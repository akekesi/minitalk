#include "minitalk.h"

int	ft_atoi(const char *str);

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	while (*str && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
