# include "minitalk.h"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    write(1, "client\n", 7);

    return 0;
}

