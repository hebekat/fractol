/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tohebeka <tohebeka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 22:28:17 by tohebeka      #+#    #+#                 */
/*   Updated: 2022/03/25 17:37:16 by tohebeka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_clicked(int event, int mouse_x, int mouse_y, t_vars *vars)
{
	long double	xdif;
	long double	ydif;

	if (event == 1)
	{		
		xdif = map_mouse_to_set(mouse_x, 1, vars->box)
			- (vars->box.x_max + vars->box.x_min) / 2;
		ydif = map_mouse_to_set(mouse_y, 0, vars->box)
			- (vars->box.y_max + vars->box.y_min) / 2;
		vars->box.x_max += xdif;
		vars->box.x_min += xdif;
		vars->box.y_max += ydif;
		vars->box.y_min += ydif;
	}
	if (event == 4)
		zoom(vars, event);
	if (event == 5)
		zoom(vars, event);
	generate_img(0, 0, vars);
	return (0);
}

void	add_offset(t_vars *vars, long double range, int axis, int mode)
{
	if (axis)
	{
		vars->box.x_max += range * mode;
		vars->box.x_min += range * mode;
	}
	else
	{
		vars->box.y_max += range * mode;
		vars->box.y_min += range * mode;
	}
}

int	reset_img(int key, t_vars *vars)
{
	long double	rangex;
	long double	rangey;

	rangex = (vars->box.x_max - vars->box.x_min) * 0.1;
	rangey = (vars->box.y_max - vars->box.y_min) * 0.1;
	if (key == 1)
	{
		vars->box.x_max = 2;
		vars->box.x_min = -2;
		vars->box.y_max = 2;
		vars->box.y_min = -2;
		vars->zoom_level = 0.3;
	}
	else if (key == 124)
		add_offset(vars, rangex, 1, 1);
	else if (key == 123)
		add_offset(vars, rangex, 1, -1);
	else if (key == 125)
		add_offset(vars, rangey, 0, 1);
	else if (key == 126)
		add_offset(vars, rangey, 0, -1);
	return (0);
}
