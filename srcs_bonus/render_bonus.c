/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:17:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/31 13:46:28 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_update_screen(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		exit_file(data, "Mlx new img failed");
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.len, &data->img.endian);
	if (!data->img.addr)
		exit_file(data, "Mlx get addr img failed");
	raycast(data);
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->img.window, data->img.img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 32)
		action_door(data);
	else if (keycode == 1731 || keycode == 119)
		movements_forward(data);
	else if (keycode == 1753 || keycode == 115)
		movements_backward(data);
	else if (keycode == 1730 || keycode == 100)
		movements_right(data);
	else if (keycode == 1738 || keycode == 97)
		movements_left(data);
	else if (keycode == 65361)
		rotation_left(data);
	else if (keycode == 65363)
		rotation_right(data);
	render_update_screen(data);
	return (0);
}

void	render(t_data *data)
{
	render_player_init(data);
	data->img.window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->img.window)
		exit_file(data, "Mlx new window failed");
	render_update_screen(data);
	mlx_loop_hook(data->mlx, &handle_no_event, &data->img);
	mlx_hook(data->img.window, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->img.window, 17, 1L << 17, &handle_cross, data);
	mlx_key_hook(data->img.window, &key_hook, data);
	mlx_hook(data->img.window, 6, 1L << 6, &rotation_mouse_move, data);
	mlx_loop(data->mlx);
	mlx_destroy_window(data->mlx, data->img.window);
}
