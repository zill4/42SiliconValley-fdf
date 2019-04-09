
#include <fdf.h>

static t_plot	*list_to_array(t_plot *plot, t_list *rows)
{
	int		y;
	int		x;
	char	**buff;
	int		z;
	// Allocate for them points which are the three 3-Dimensional points world, local, aligned
	plot->points = (t_vertex ***)ft_memalloc(sizeof(t_vertex **)
		* plot->height);
	y = -1;
	// Go through the matrix
	while (++y < plot->height)
	{
		// alloc for array of points to be allocated times the size of the width.
		plot->points[y] = (t_vertex **)ft_memalloc(sizeof(t_vertex *)
			* plot->width);
		// split the content of the list that was created and push to a buffer string.
		buff = ft_strsplit(rows->content, ' ');
		x = -1;
		// for the length of the array 
		while (++x < plot->width)
		{
			// basically translate each split item into a integer
			z = ft_atoi(buff[x]);
			// plot each point by taking the value given as the z the current x and y from the loops
			//plot the points for local are only set, world, and aligned are zero'd
			plot->points[y][x] = ft_make_vertex(x, y, z);
			// check for min and save to z_min max
			plot->z_min = MIN(z, plot->z_min);
			plot->z_max = MAX(z, plot->z_max);
		}
		// go through each row.
		rows = rows->next;
	}
	// return the completed plot.
	return (plot);
}
// Given a file returns a complete plot.

t_plot			*parse_file(char *filename)
{
	// We have our buffer for gnl
	char	*buff;
	// The true/false result of our read.
	int		result;
	// our file descriptor
	int		fd;
	// Generic linked list object
	t_list	*list;
	// Our plot...
	t_plot	*plot;
	// malloc for the plot
	plot = (t_plot *)ft_memalloc(sizeof(t_plot));
	// init the width to -1
	plot->width = -1;
	// open up the file 
	fd = open(filename, O_RDONLY);
	// init the list to null
	list = NULL;
	// use int max and min for the z min max vals
	plot->z_min = 2147483647;
	plot->z_max = -2147483648;
	// read from the file.
	while ((result = get_next_line(fd, &buff)) > 0)
	{
		// If this is our first iteration...
		if (plot->width == -1)
			plot->width = ft_count_words(buff, ' ');
		// counts the number of words delimnated by ' ' 
		if (plot->width != ft_count_words(buff, ' '))
			ft_error("Invalid Map");
		// After plotting for the first time, we check that all lines keep the same 
		// width. append each string to the list.
		ft_append(&list, ft_lstnew(buff, ft_strlen(buff) + 1));
		// Increase the height as we check width
		(plot->height)++;
	}
	// Error reading
	if (result < 0)
		ft_error_unknown();
	close(fd);
	// Translate our list of strings into a matrix.
	return (list_to_array(plot, list));
}
