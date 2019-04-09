#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include "../libgfx/libgfx.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>


# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 6
# define KEY_ZOOM_OUT 7

# define KEY_ROT_X_U 13
# define KEY_ROT_X_D 1
# define KEY_ROT_Y_U 0
# define KEY_ROT_Y_D 2
# define KEY_ROT_Z_U 12
# define KEY_ROT_Z_D 14

t_plot		*parse_file(char *filename);
void		draw(t_data *d);
int			key_hook(int keycode, t_data *d);
void		draw_reload(t_data *d);
void		ft_exit(void);
void		ft_error(char *s);
void		ft_error_unknown(void);
int			expose_hook(t_data *d);

#endif
