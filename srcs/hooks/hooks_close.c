
#include "../../includes/cub3d.h"

int	handle_input(int keysym, t_data *data)
{
	if (keysym == 65307 && data->img.window != 0)
	{
		mlx_loop_end(data->mlx);
	}
	return (0);
}

int	handle_cross(t_data *data)
{
	if (data->img.window != 0)
		return (handle_input(65307, data));
	return (0);
}

/* This function needs to exist, but it is useless for the moment */
int	handle_no_event(void)
{
	return (0);
}
