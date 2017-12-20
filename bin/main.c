#include "fdf.h"

int		close_event(int key, void *map)
{
	if (key == 53)
	{
		mlx_destroy_window(((t_map*)map)->cid, ((t_map*)map)->wid);
		exit(0);
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	int		fd;
	t_map	map;

	if (argc != 2)
	{
		ft_putendl_fd("tg", 2);
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 3
	||	parse(fd, &map))
		return (1);
	map.cid = mlx_init();
	map.wid = mlx_new_window(map.cid, WSX, WSY, "FdF");
	display(&map);
	mlx_key_hook (map.wid, &close_event, &map);
	mlx_loop(map.cid);
	return (0);
}
