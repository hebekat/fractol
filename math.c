/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tohebeka <tohebeka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 14:40:04 by tohebeka      #+#    #+#                 */
/*   Updated: 2022/03/25 17:47:41 by tohebeka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	map_mouse_to_set(long double pos, int axis, t_box box)
{
	if (axis)
		pos = (pos / WIDTH) * (box.x_max - box.x_min) + box.x_min;
	else
		pos = ((pos / HEIGTH) * (box.y_max - box.y_min) + box.y_min);
	return (pos);
}

float	lerp(float v0, float v1, float t)
{
	return ((1 - t) * v0 + t * v1);
}

int	colerp(int color1, int color2, float fraction)
{
	t_rgb	color;

	color.r1 = (color1 >> 16) & 0xff;
	color.r2 = (color2 >> 16) & 0xff;
	color.g1 = (color1 >> 8) & 0xff;
	color.g2 = (color2 >> 8) & 0xff;
	color.b1 = color1 & 0xff;
	color.b2 = color2 & 0xff;
	return ((int)((color.r2 - color.r1) * fraction + color.r1) << 16 |
			(int)((color.g2 - color.g1) * fraction + color.g1) << 8 |
			(int)((color.b2 - color.b1) * fraction + color.b1));
}

void	zoom(t_vars *vars, int event)
{
	long double	xzoom;
	long double	yzoom;
	long double	zoom_factor;

	zoom_factor = 0.2;
	xzoom = (vars->box.x_max - vars->box.x_min) * zoom_factor;
	yzoom = (vars->box.y_max - vars->box.y_min) * zoom_factor;
	if (event == 4)
	{
		vars->box.x_max -= xzoom;
		vars->box.x_min += xzoom;
		vars->box.y_max -= yzoom;
		vars->box.y_min += yzoom;
		vars->length = vars->length * vars->zoom_level;
	}
	if (event == 5)
	{
		vars->box.x_max += xzoom;
		vars->box.x_min -= xzoom;
		vars->box.y_max += yzoom;
		vars->box.y_min -= yzoom;
		vars->length = vars->length * vars->zoom_level;
	}
}
