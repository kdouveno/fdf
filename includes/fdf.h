#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# define WSX 1600
# define WSY 900
# define MZ 1
# define MY 0.9
# define MARGIN 100
# define MAXC 0x00ff0000
# define MINC 0x00ffffff
#         include <stdio.h>

typedef struct		s_sd
{
	double			xmax;
	double			ymax;
	double			xmin;
	double			ymin;
}					t_sd;

typedef struct		s_2d
{
	double			x;
	double			y;
	int				h;
}					t_2d;

typedef struct		s_set2d
{
	t_2d			*pts;
	struct s_set2d	*next;
}					t_set2d;

typedef struct		s_map
{
	int				hmax;
	int				hmin;
	size_t			len;
	void			*cid;
	void 			*wid;
	int 			*image;
	t_set2d			*set;

}					t_map;

typedef struct	s_rgb
{
	unsigned int r : 8;
	unsigned int g : 8;
	unsigned int b : 8;
	unsigned int : 8;
}				t_rgb;

typedef union	u_color
{
	unsigned int	color;
	t_rgb			rgb;
}				t_color;

void				display(t_map *map);
int					parse(int fd, t_map *map);

#endif
