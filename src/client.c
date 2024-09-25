// TODO: comments, descriptions
// TODO: error handling: sigaction, write, putstr
// TODO: check, whether signal comming from server?
// TODO: answer only for server!

#include "minitalk.h"

t_info_client	g_info_client;

static void	init_info(char *message);
static void	update_info(void);
static void	init_signal(void);
static void	print_first(char *pid_str);
static void	print_last(void);
static void	fetch_bit(pid_t pid);
static void	signal_handler(int signal, siginfo_t *info, void *context);
static int	check_args(int argc, char **argv);

static void	init_info(char *message)
{
	g_info_client.first = 1;
	g_info_client.n_bit = 0;
	g_info_client.n_char = 0;
	g_info_client.n_message = 0;
	g_info_client.message = message;
}

static void	update_info()
{
	g_info_client.n_bit = 0;
	g_info_client.n_char++;
	g_info_client.n_message++;
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

static void	print_first(char *pid_str)
{
	ft_putstr(g_info_client.message);
	ft_putstr("\nis sent to the server-");
	ft_putstr(pid_str);
	ft_putstr("\n");
}

static void	print_last(void)
{
	char	*n_message_str;

	n_message_str = ft_itoa(g_info_client.n_message);

	ft_putstr("sent last\n");
	ft_putstr("length of sent message: ");
	ft_putstr(n_message_str);
	ft_putstr("\n");

	free(n_message_str);
}

static void	fetch_bit(pid_t pid)
{
	if ((g_info_client.message[g_info_client.n_char] >> (7 - g_info_client.n_bit)) & 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	g_info_client.n_bit++;
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;

	g_info_client.first = 0;

	if (signal == SIGUSR1)
	{
		if (g_info_client.n_bit < 8)
			fetch_bit(info->si_pid);
		if (g_info_client.n_bit == 8)
		{
			if (!g_info_client.message[g_info_client.n_char])
			{
				print_last();
				exit(EXIT_SUCCESS);
			}
			update_info();
		}
	}
}

static int	check_args(int argc, char **argv)
{
	int	n;

	if (argc != 3)
	{
		ft_putstr("Error: argc != 3\n");
		ft_putstr("Usage: ./bin/client <pid_of_server> <message_to_send>\n");
		return (0);
	}
	n = ft_atoi(argv[1]);
	if (n < 0)
	{
		ft_putstr("Error: pid < 0\n");
		return (0);
	}
	if (n == 0)
	{
		ft_putstr("Error: pid == 0\n");
		return (0);
	}
	if (!ft_isdigits(argv[1]))
	{
		ft_putstr("Error: invalid pid\n");
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	pid_t	pid_server_int;

	if (check_args(argc, argv))
	{
		pid_server_int = (pid_t)ft_atoi(argv[1]);
		
		init_signal();
		init_info(argv[2]);
	
		print_first(argv[1]);

		kill(pid_server_int, SIGUSR1);

		while(1)
		{
			sleep(3);
			if (g_info_client.first == 1)
			{
				ft_putstr("Error: no feedback\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (0);
}
