#include "minitalk.h"

char		*ft_itoa(int n);
static int	hf_calc_digits(int n);

char	*ft_itoa(int n)
{
	int		i;
	long	n_;
	char	*str;

	i = hf_calc_digits(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (!n)
	{
		str[i--] = '0';
		return (str);
	}
	n_ = n;
	if (n_ < 0)
		n_ *= -1;
	while (n_)
	{
		str[i--] = '0' + (n_ % 10);
		n_ /= 10;
	}
	if (!i)
		str[i] = '-';
	return (str);
}

static int	hf_calc_digits(int n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
