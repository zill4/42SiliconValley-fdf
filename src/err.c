

#include "fdf.h"

void	ft_exit(void)
{
	exit(1);
}

void	ft_error(char *s)
{
	//ft_putendl_fd(s, 2);
    ft_printf("%s\n", s);
	ft_exit();
}

void	ft_error_unknown(void)
{
	ft_putstr("Error: ");
	//ft_error(strerror(errno));
}
