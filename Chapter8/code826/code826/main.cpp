#include <cstdio>
#include <assert.h>
#include "csapp.h"
#include "shell.h"
#include "job.h"

void eval(char* cmdline)
{
	char *argv[MAXARGS];	// argument list execve()
	char buf[MAXLINE];		// holds modified command line
	int bg;
	pid_t pid;

	strcpy(buf, cmdline);
	bg = parse_line(buf, argv);
	if (argv[0] == NULL)
	{
		return;
	}

	if (!builtin_command(argv))
	{
		sigset_t mask_one, prev_one;
		Sigemptyset(&mask_one);
		Sigemptyset(&mask_one, SIGCHLD);

		/* block signal child */
		Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);
		if ((pid = Fork()) == 0)
		{
			/* unblock in child process */
			Sigprocmask(SIG_SETMASK, &prev_one, NULL);

			/* set gid same like pid */
			Setpgid(0, 0);

			if (Execve(argv[0], argv, environ) < 0)
			{
				printf("%s: command not found.\n",
					argv[0]);
			}
		}

		sigset_t mask_all, prev_all;
		Sigfillset(&mask_all);

		// save job info
		Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
		Jid new_jid = new_job(pid, cmdline, !bg);
		Sigprocmask(SIG_SETMASK, &prev_all, NULL);

		if (!bg)
		{
			set_fg_pid(pid);
			while (get_fg_pid())
			{
				Sigsuspend(&prev_one);
			}
		}

		else
		{
			printf("[%d] %d %s \t %s\n", new_jid, pid,
				"Running", cmdline);
		}
		Sigprocmask(SIG_SETMASK, &prev_one, NULL);
	}

	return;
}

int builtin_command(char **argv)
{
	/*
	if first arg is a builtin command, run it and
	return true;
	else return false
	*/

	if (!strcmp(argv[0], "quit"))	// quit command
	{
		exit(0);
	}
	if (!strcmp(argv[0], "&"))
	{
		return 1;
	}
	if (!strcmp(argv[0], "jobs"))
	{
		print_jobs();
		return 1;
	}

	// > fg
	if (!strcmp(argv[0], "fg"))
	{
		int id;
		// right format: fg %ddd or fg ddd
		if ((id = parse_id(argv[1])) != -1 &&
			argv[2] == NULL)
		{
			sigset_t mask_one, prev_one;
			Sigemptyset(&mask_one);
			Sigaddset(&mask_one, SIGCHLD);
			Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);

			pid_t pid = id;
			// if param is jid
			if (argv[1][0] == '%')
			{
				JobPtr jp = find_job_by_jid(id);
				pid = jp->pid;
			}
			Kill(pid, SIGCONT);
			set_fg_pid(pid);
			while (get_fg_pid())
			{
				Sigsuspend(&prev_one);
			}

			Sigprocmask(SIG_SETMASK, &prev_one, NULL);
		}
		else
		{
			printf("format error ,e.g. fg %%12 || fg 1498\n");
		}

		return 1;
	}

	// > bg
	if (!strcmp(argv[0], "bg"))
	{
		int id;
		// right format: bg %ddd or bg ddd
		if ((id = parse_id(argv[1])) != -1 &&
			argv[2] == NULL)
		{
			pid_t pid = id;
			// jid param
			if (argv[1][0] == '%')
			{
				JobPtr jp = find_job_by_jid(id);
				pid = jp->pid;
			}
			Kill(pid, SIGCONT);
		}
		else
		{
			printf("format error, e.g. bg %%12 or bg 1498\n");
		}
		return 1;
	}

	return 0;
}

int parse_line(char* buf, char **argv)
{
	/* 
	parse_line -parse the command line and build the argv
	array
	*/

	char* delim;	// points to first space delimiter
	int argc;		// number of args
	int bg;			// backgroup job

	buf[strlen(buf) - 1] = ' ';	// replace trailing '\n' with space

	while (*buf && (*buf == ' '))
	{
		buf++;
	}

	// build the argv list
	argc = 0;
	while ((delim = strchr(buf, ' ')))
	{
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (buf && (*buf == ' '))
		{
			buf++;
		}
	}
	argv[argc] = NULL;

	if (argc == 0)
	{
		return 1;
	}
	/* should the job run in the backgroud */
	if ((bg = (*argv[argc - 1] == '&')) != 0)
	{
		argv[--argc] == NULL;
	}

	return bg;
}

static int is_number_str(char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++)
		if (!isdigit(s[i]))
			return 0;
	return 1;
}

int parse_id(char* s) {
	int error = -1;
	if (s == NULL)
		return error;
	/* format: %ddddd */
	if (s[0] == '%') {
		if (!is_number_str(s + 1))
			return error;
		return atoi(s + 1);
	}	//format: dddddd
	if (is_number_str(s))
		return atoi(s);

	/* not right */
	return error;
}

void test_shell()
{
	assert(-1 == parse_id("ns"));
	assert(-1 == parse_id("%%"));
	assert(0 == parse_id("%0"));
	assert(0 == parse_id("0"));
	assert(98 == parse_id("%98"));
	assert(98 == parse_id("98"));
}

int main()
{
    printf("hello from code826!\n");
    return 0;
}