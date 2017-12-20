#include "fdf.h"

static int		add_line(t_set2d **set, size_t len)
{
	t_set2d	*m;

	m = NULL;
	if (*set)
		m = *set;
	if(!(*set = (t_set2d*)malloc(sizeof(t_set2d))))
		return (1);
	if (!((*set)->pts = (t_2d*)malloc(sizeof(t_2d) * len)))
		return (1);
	(*set)->next = m;
	return (0);
}

static int		ft_map(char **tab, t_set2d **set, size_t len, int *hmax)
{
	static int	y;
	int			x;
	double		an;

	if (add_line(set, len))
		return (1);
	x = 0;
	while (tab[x])
	{
		an = atan2(y, x) + M_PI_4;
		(*set)->pts[x].h = ft_atoi(tab[x]);
		if ((*set)->pts[x].h > *hmax)
			*hmax = (*set)->pts[x].h;
		(*set)->pts[x].x = (cos(an) * hypot(x, y));
		(*set)->pts[x].y = ((sin(an) * hypot(x, y)) - (*set)->pts[x].h * MZ) * MY;
		x++;
	}
	y++;
	return (0);
}

static void get_setdescriptor(t_set2d *set, t_sd *sd, size_t len)
{
	size_t i;

	sd->xmax = set->pts[0].x;
	sd->xmin = sd->xmax;
	sd->ymax = set->pts[0].y;
	sd->ymin = sd->ymax;
	while (set)
	{
		i = 0;
		while (i < len)
		{
			sd->xmax = set->pts[i].x > sd->xmax ? set->pts[i].x : sd->xmax;
			sd->xmin = set->pts[i].x < sd->xmin ? set->pts[i].x : sd->xmin;
			sd->ymax = set->pts[i].y > sd->ymax ? set->pts[i].y : sd->ymax;
			sd->ymin = set->pts[i].y < sd->ymin ? set->pts[i].y : sd->ymin;
			i++;
		}
		set = set->next;
	}

}

static void		ooffset(t_set2d *set, t_sd *sd, size_t len)
{
	size_t i;


	while (set)
	{
		i = 0;
		while (i < len)
		{
			set->pts[i].x -= sd->xmin;
			set->pts[i].y -= sd->ymin;
			i++;
		}
		set = set->next;
	}
	sd->xmax -= sd->xmin;
	sd->ymax -= sd->ymin;
}

static void multiply(t_set2d *set, t_sd *sd, size_t len)
{
	size_t		i;
	double	multiplier;

	if ((WSX - MARGIN * 2) / sd->xmax < (WSY - MARGIN * 2) / sd->ymax)
	{
		multiplier = (WSX - MARGIN * 2) / sd->xmax;
		sd->xmin = MARGIN;
		sd->ymin = ((WSY - MARGIN * 2) - sd->ymax * multiplier) / 2 + MARGIN;
	}
	else
	{
		multiplier = (WSY - MARGIN * 2) / sd->ymax;
		sd->ymin = MARGIN;
		sd->xmin = ((WSX - MARGIN * 2) - sd->xmax * multiplier) / 2 + MARGIN;
	}
	while (set)
	{
		i = 0;
		while (i < len)
		{
			set->pts[i].x = set->pts[i].x * multiplier + sd->xmin;
			set->pts[i].y = set->pts[i].y * multiplier + sd->ymin;
			i++;
		}
		set = set->next;
	}
}

static void		resize(t_set2d *set, size_t len)
{
	t_sd	sd;

	get_setdescriptor(set, &sd, len);
	ooffset(set, &sd, len);
	multiply(set, &sd, len);
}

int				parse(int fd, t_map *map)
{
	char	*line;
	char	**tab;
	size_t	i;

	map->hmax = 0;
	map->len = 0;
	while (get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ' ');
		i = 0;
		while (tab[i])
			i++;
		if (i != map->len && map->len != 0)
			return (1);
		map->len = i;
		if (ft_map(tab, &(map->set), map->len, &(map->hmax)))
			return (1);

	}
	resize(map->set, map->len);
	return (0);
}
