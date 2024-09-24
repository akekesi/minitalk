# include "minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context);

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;

	if (signal == SIGUSR1)
	{
		ft_putstr("CLIENT: sig1 --> sig2\n");
		kill(info->si_pid, SIGUSR2);
	}
	if (signal == SIGUSR2)
	{
		ft_putstr("CLIENT: sig2 --> sig1\n");
		kill(info->si_pid, SIGUSR1);
	}
}


int main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				pid_server;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;

	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	if (argc == 2)
	{
		pid_server = (pid_t)ft_atoi(argv[1]);
		ft_putstr("CLIENT:      --> sig1\n");

		kill(pid_server, SIGUSR1);

		int i;
		i = 5;
		while(i--)
		{
			pause();
		}
	}

	return 0;
}
