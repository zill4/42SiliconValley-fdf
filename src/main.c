#include "fdf.h"

#include <stdio.h>

void	usage(char *av)
{
	ft_putstr("usage: ");
	ft_putstr(av);
	ft_putendl(" input_file");
}

void	controls(void)
{
	// Literally just prints control scheme.
	ft_putendl("CONTROLS:\n\
Translations:\n\
	Y: Arrow Key: UP, DOWN\n\
	X: Arrow Key: LEFT, RIGHT\n\
Rotation:\n\
	WASD - QE\n\
    X: A, D\n\
	Y: Keypad: W, S\n\
	Z: Keypad: Q, E\n\
Zoom:\n\
	IN: Z\n\
	OUT: X");
}

int		main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = (t_data *)ft_memalloc(sizeof(t_data));
		if (!data)
			ft_error("Malloc Error");
		// generate plot object from parsing the file
		data->plot = parse_file(av[1]);
		// print the controls 
		conrols();
		// Draw the damn thing
		draw(data);
	}
	else
		usage(av[0]);
	return (0);
}
