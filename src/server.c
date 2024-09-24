// TODO: kell csekkolni, hogy az elso clienttol jon a signal?
// TODO: csak a clinettol jovore valaszoljon es csak arra!

# include "minitalk.h"

t_info_server	g_info_server;

void	init_info(void);
void	update_info(void);

void	init_signal(void);

void	print_first(pid_t pid);
void	print_char(void);
void	print_last(void);

void	build_char(int signal);

void	signal_handler(int signal, siginfo_t *info, void *context);


void	init_info(void)
{
	g_info_server.first = 1;
	g_info_server.n_bit = 0;
	g_info_server.n_char = 0;
	g_info_server.n_message = 0;
	g_info_server.char_ = 0;
}

void	update_info(void)
{
	g_info_server.n_bit = 0;
	g_info_server.n_char++;
	g_info_server.n_message++;
	g_info_server.char_ = 0;
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;

	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

void	print_first(pid_t pid)
{
	char	*pid_server_str;

	pid_server_str = ft_itoa(pid);

	ft_putstr("server pid: ");
	ft_putstr(pid_server_str);
	ft_putstr("\n");

	free(pid_server_str);
}

void	print_char(void)
{
		write(1, &g_info_server.char_, 1);
}

void	print_last(void)
{
	char	*n_message_str;

	n_message_str = ft_itoa(g_info_server.n_message);

	ft_putstr("\ngot last\n");
	ft_putstr("length of received message: ");
	ft_putstr(n_message_str);
	ft_putstr("\n");

	free(n_message_str);
}

void	build_char(int signal)
{
	if (signal == SIGUSR1)
		g_info_server.char_ = (g_info_server.char_ << 1) | 1;
	if (signal == SIGUSR2)
		g_info_server.char_ = (g_info_server.char_ << 1) | 0;
	g_info_server.n_bit++;
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;

	if (g_info_server.first)
	{
		kill(info->si_pid, SIGUSR1);
		g_info_server.first = 0;
		return ;
	}
	if (g_info_server.n_bit < 8)
		build_char(signal);
	if (g_info_server.n_bit == 8)
	{
		if (!g_info_server.char_)
		{
			print_last();
			init_info();
			return ;
		}
		print_char();
		update_info();
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();

	init_info();
	init_signal();
	print_first(pid);

	while (1)
		pause();

	return 0;
}
