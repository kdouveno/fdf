#include "mlx.h"

int main()
{
	void *idc;
	void *idw;

	idc = mlx_init();
	idw = mlx_new_window(idc, 500, 500, "LA FENETRE");
	mlx_pixel_put(idc, idw, 50, 50, 0x005b412b);
	mlx_loop(idc);
	return 0;
}
