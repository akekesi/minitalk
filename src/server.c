// TODO: comments, descriptions
// TODO: error handling: sigaction, write, putstr
// TODO: check, whether signal comming from client?
// TODO: answer only for client!

#include "minitalk.h"

t_info_server	g_info_server;

static void	init_info(void);
static void	update_info(void);
static void	init_signal(void);
static void	print_first(pid_t pid);
static void	print_char(void);
static void	print_last(void);
static void	build_char(int signal);
static void	signal_handler(int signal, siginfo_t *info, void *context);

static void	init_info(void)
{
	g_info_server.first = 1;
	g_info_server.n_bit = 0;
	g_info_server.n_char = 0;
	g_info_server.n_message = 0;
	g_info_server.char_ = 0;
}

static void	update_info(void)
{
	g_info_server.n_bit = 0;
	g_info_server.n_char++;
	g_info_server.n_message++;
	g_info_server.char_ = 0;
}

static void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;

	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

static void	print_first(pid_t pid)
{
	char	*pid_server_str;

	pid_server_str = ft_itoa(pid);

	if (!pid_server_str)
	{
		ft_putstr("Error: ft_itoa failed\n");
		exit(EXIT_FAILURE);
	}

	ft_putstr("server pid: ");
	ft_putstr(pid_server_str);
	ft_putstr("\n");

	free(pid_server_str);
}

static void	print_char(void)
{
	write(1, &g_info_server.char_, 1);
}

static void	print_last(void)
{
	char	*n_message_str;

	n_message_str = ft_itoa(g_info_server.n_message);

	ft_putstr("\ngot last\n");
	ft_putstr("length of received message: ");
	ft_putstr(n_message_str);
	ft_putstr("\n");

	free(n_message_str);
}

static void	build_char(int signal)
{
	if (signal == SIGUSR1)
		g_info_server.char_ = (g_info_server.char_ << 1) | 1;
	if (signal == SIGUSR2)
		g_info_server.char_ = (g_info_server.char_ << 1) | 0;
	g_info_server.n_bit++;
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
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
	return (0);
}
