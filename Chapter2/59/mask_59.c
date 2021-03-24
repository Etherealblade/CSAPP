#include <assert.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    size_t mask = 0xff;
    size_t x = 0x89ABCDEF;
    size_t y = 0x76543210;

    size_t result = (x & 0xff) | (y & -mask);
    assert(result == 0x765432EF);

    return 0;
}
