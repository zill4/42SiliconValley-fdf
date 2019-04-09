
#include "fdf.h"

void	draw_map(t_data *d)
{
	int x;
	int y;

	y = -1;
	// work actually done here using the 3d draw functions from libgfx
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			if (y < d->plot->height - 1)
				ft_3d_drawline(d, *d->plot->points[y][x]->aligned,
					*d->plot->points[y + 1][x]->aligned);
			if (x < d->plot->width - 1)
				ft_3d_drawline(d, *d->plot->points[y][x]->aligned,
					*d->plot->points[y][x + 1]->aligned);
		}
	}
}

void	setup_world(t_data *d)
{
	// this is a lie?
	float	global_matrix[4][4];
	int		x;
	int		y;
	// zero this out to as a 4x4 matrix
	ft_make_identity_matrix(global_matrix);
	// Do the math to make this matrix work
	ft_tr_translate(global_matrix,
		-(d->plot->width / 2),
		-(d->plot->height / 2),
		0);
	y = -1;
	// From our data we go through the matrix
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			//calculate the saved point information and calc the local dimension, global is a trnanslation to
			// half the width and height. 
			// world is zero'd 
			ft_vec_mult_mat(d->plot->points[y][x]->local,
				global_matrix,
				d->plot->points[y][x]->world);
		}
	}
}

void	calc_aligned(t_data *d)
{
	float	global_matrix[4][4];
	int		y;
	int		x;
	// zero our global matrix 
	ft_make_identity_matrix(global_matrix);
	// set the roations from your x/y/z rot
	ft_tr_rotate(global_matrix, d->xr, d->yr, d->zr);
	// scale to our set devided by the dimensions of width/height
	ft_tr_scale(global_matrix,
		(WINDOW_SIZE_X * d->scale) / d->plot->width,
		(WINDOW_SIZE_Y * d->scale) / d->plot->height, 0);
	// check our translate from data and translate by that divided by window size.
	ft_tr_translate(global_matrix,
		WINDOW_SIZE_X / 2 + d->xtrans,
		WINDOW_SIZE_Y / 2 + d->ytrans, 0);
	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			// calculate from our world, global and aligned current values of map.
			ft_vec_mult_mat(d->plot->points[y][x]->world,
				global_matrix, d->plot->points[y][x]->aligned);
			d->plot->points[y][x]->aligned->z =
			d->plot->points[y][x]->local->z;
		}
	}
}

void	draw_reload(t_data *d)
{
	// setup for the alignment
	calc_aligned(d);
	// setup image to start drawing.
	d->img = mlx_new_image(d->mlx, WINDOW_SIZE_X + 100, WINDOW_SIZE_Y + 100);
	// from image save our bpp, line, and ed as we begin to translate each to the pixel
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	draw_map(d);
	// now that we have our map drawn and the img created we pushing to the window
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	// deleting it right after to free memory 
	mlx_destroy_image(d->mlx, d->img);
}

void	draw(t_data *d)
{
	// initialized the perspective
	d->xr = 0.7;
	d->yr = 0.7;
	d->zr = 0.1;
	// ----
	d->scale = 0.5;
	d->ytrans = 0;
	d->xtrans = 0;
	// basically size it out to 0
	d->mlx = mlx_init(); //init our mlx
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "FdF"); //send our static window size
	// setup those colors
	init_color_table(d);
	// prepare the colors
	setup_world(d);
	// setup the world 
	// expose the hooks
	mlx_expose_hook(d->win, expose_hook, d);
	//we listen for those translators 
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_loop(d->mlx);
	// loop just keeps this process repeating.
}
