
#include "libgfx.h"

t_3d		*ft_make_3d(int x, int y, int z)
{
	t_3d *ret;

	ret = (t_3d *)ft_memalloc(sizeof(t_3d));
	ret->x = x;
	ret->y = y;
	ret->z = z;
	return (ret);
}

t_vertex	*ft_make_vertex(int x, int y, int z)
{
	t_vertex *ret;

	ret = (t_vertex *)ft_memalloc(sizeof(t_vertex));
	ret->local = ft_make_3d(x, y, z);
	ret->world = ft_make_3d(0, 0, 0);
	ret->aligned = ft_make_3d(0, 0, 0);
	return (ret);
}
