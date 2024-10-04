#include "minitalk.h"

/**
 * @brief Outputs a string to the standard output (stdout).
 * 
 * This function takes a string as input and writes each character to the 
 * standard output one by one, using the write() system call.
 * 
 * @param str Pointer to the null-terminated string to be printed.
 * 
 * @note This function does not append a newline at the end of the string.
 */
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
}
