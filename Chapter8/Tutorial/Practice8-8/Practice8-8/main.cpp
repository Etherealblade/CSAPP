#include <cstdio>
#include "csapp.h"
/* 
P799, P825
源代码kill函数发送的是sigusr1信号, 但是即使注释掉signal blocking
代码块也照样得到预期输出:213.

但是,若把sigusr1改成sigkill, signal blocking 代码块才体现出他的意义:
阻拦一个信号, 使得被保护的代码区域得以不被中断!
可是却得不到预期的输出
*/

volatile long counter = 2;
void handler1(int sig)
{
	sigset_t mask, prev_mask;

	//Sigfillset(&mask);	// P791, Figure8.32
	//Sigprocmask(SIG_BLOCK, &mask, &prev_mask); /* Block sigs */
	//
	//// 断点,无法调试
	Sio_putl(--counter);	// 1
	Sio_puts("\n");	// Code region that will not be interrupted by SIG*
	//
	//Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /* Restore sigs */

	_exit(0);
}

int main()
{
	pid_t pid;
	sigset_t mask, prev_mask;

	printf("%d\n", counter);	// 2
	fflush(stdout);

	signal(SIGUSR1, handler1);
	if ((pid = Fork()) == 0) 
	{
		//pid_t p_child = getpid();
		//Sio_puts("p_child: \n");
		//Sio_putl(p_child);
		//Sio_puts("\n");
		//
		//pid_t p_prt = getppid();
		//Sio_puts("p_prt: \n");
		//Sio_putl(p_prt);
		//Sio_puts("\n");
		
		while (1) 
		{
			/*
			这个无限循环有点让人胆寒,但是子进程的
			作用域让人舒服
			*/
		}

	}

	// Parent proc:
	Kill(pid, SIGUSR1);	// whose pid? Answer says it's child's
	//Sio_putl(pid);
	//Sio_puts("\n");
	Waitpid(-1, NULL, 0);

	//Sigfillset(&mask);		// Temporarily blocking a signal from being received
	//Sigprocmask(SIG_BLOCK, &mask, &prev_mask); /* Block sigs */
	//
	printf("%d\n", ++counter);	// 3
	//
	//Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /* Restore sigs */

	exit(0);
}