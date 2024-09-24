#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_info_server
{
	int		first;
	int		n_bit;
	int		n_char;
	int		n_message;
	char	char_;
}	t_info_server;

typedef struct s_info_client
{
	int		first;
	int		n_bit;
	int		n_char;
	int		n_message;
	char	*message;
}	t_info_client;

// server.c

// client.c

// ft_atoi.c
int 	ft_atoi(const char *str);

// ft_is.c
int 	ft_isdigit(int c);
int 	ft_isdigits(char *str);
int 	ft_isspace(int c);

// ft_itoa.c
char	*ft_itoa(int n);

// ft_putstr.c
void	ft_putstr(char *str);

#endif
