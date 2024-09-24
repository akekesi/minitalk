# include "minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context);

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;

	if (signal == SIGUSR1)
	{
		ft_putstr("SERVER: sig1 --> sig1\n");
		kill(info->si_pid, SIGUSR1);
	}
	if (signal == SIGUSR2)
	{
		ft_putstr("SERVER: sig2 --> sig2\n");
		kill(info->si_pid, SIGUSR2);
	}

}

int	main(void)
{
	struct sigaction	sa;
	char				*pid_server_str;

	pid_server_str = ft_itoa(getpid());

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;

	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	ft_putstr("server pid: ");
	ft_putstr(pid_server_str);
	ft_putstr("\n");

	free(pid_server_str);

	while (1)
		pause();

	return 0;
}
