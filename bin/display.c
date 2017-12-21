#include "fdf.h"

static void draw_info(t_2d *vec, double *i) {
	if (fabs(vec->x) > fabs(vec->y))
	{
		*i = fabs(vec->x);
		vec->y /= fabs(vec->x);
		vec->x /= fabs(vec->x);
	}
	else
	{
		*i = fabs(vec->y);
		vec->x /= fabs(vec->y);
		vec->y /= fabs(vec->y);
	}
}

static t_color	get_color(int hmax, int hmin, int h)
{
	t_color out;
	t_color max;
	t_color min;

	max.color = MAXC;
	out.color = 0;
	min.color = MINC;
	h -= hmin;
	hmax -= hmin;
	if (hmax)
	{
		out.rgb.r = min.rgb.r + h * (max.rgb.r - min.rgb.r) / hmax;
		out.rgb.g = min.rgb.g + h * (max.rgb.g - min.rgb.g) / hmax;
		out.rgb.b = min.rgb.b + h * (max.rgb.b - min.rgb.b) / hmax;
	}
	else
		out.color = MINC;
	return (out);
}

void	cvecinit(double cvec[6], double i, t_color start, t_color end)
{
	cvec[0] = i ? (end.rgb.r - start.rgb.r) / i : 0;
	cvec[1] = i ? (end.rgb.g - start.rgb.g) / i : 0;
	cvec[2] = i ? (end.rgb.b - start.rgb.b) / i : 0;
	cvec[3] = start.rgb.r;
	cvec[4] = start.rgb.g;
	cvec[5] = start.rgb.b;
}

void	cvecapply(double cvec[6], t_color *start)
{
	cvec[3] += cvec[0];
	cvec[4] += cvec[1];
	cvec[5] += cvec[2];
	start->rgb.r = cvec[3];
	start->rgb.g = cvec[4];
	start->rgb.b = cvec[5];
}

void	drawline(t_map *map, t_2d pt1, t_2d pt2)
{
	t_2d vec;
	double i;
	t_color start;
	t_color end;
	double cvec[6];

	start = get_color(map->hmax, map->hmin, pt1.h);
	end = get_color(map->hmax, map->hmin, pt2.h);
	vec = (t_2d){pt2.x - pt1.x, pt2.y - pt1.y, 0};
	draw_info(&vec, &i);
	cvecinit(cvec, i, start, end);
	while (i >= 0)
	{
		map->image[(int)pt1.y * (int)WSX + (int)pt1.x] = start.color;
		pt1.x += vec.x;
		pt1.y += vec.y;
		cvecapply(cvec, &start);
		i--;
	}
}

void rec_display(t_map *map, t_set2d *set)
{
	size_t i;

	if (set->next)
		rec_display(map, set->next);
	i = 0;
	while (i < map->len)
	{
		if (set->next)
			drawline(map, set->pts[i], set->next->pts[i]);
		if (i + 1 < map->len)
			drawline(map, set->pts[i], set->pts[i + 1]);
		i++;
	}
}

void	display(t_map *map)
{
	int		getter[3];
	void	*iid;

	iid = mlx_new_image(map->cid, WSX, WSY);
	map->image = (int*)mlx_get_data_addr(iid, getter, getter + 1, getter + 2);
	rec_display(map, map->set);
	mlx_put_image_to_window(map->cid, map->wid, iid, 0, 0);
}
