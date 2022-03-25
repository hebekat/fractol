/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   equations.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tohebeka <tohebeka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 14:40:04 by tohebeka      #+#    #+#                 */
/*   Updated: 2022/03/25 17:55:38 by tohebeka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	mandelbrot_core(t_complex comp, long double x,
long double y, int max_iter)
{
	while (comp.x_s + comp.y_s <= 20 && comp.iteration < max_iter)
	{
		comp.xtemp = comp.x_s - comp.y_s + comp.c_x;
		y = 2 * x * y + comp.c_y;
		x = comp.xtemp;
		comp.x_s = x * x;
		comp.y_s = y * y;
		comp.iteration++;
	}
	if (comp.iteration < max_iter)
	{
		comp.log_zn = log(comp.x_s + comp.y_s) * 0.5 ;
		comp.nu = log(comp.log_zn * 1.3) * 1.3;
		comp.iteration = comp.iteration + 1 - comp.nu;
	}
	return (comp);
}

long double	mandelbrot(long double x, long double y, t_vars *vars, int max_iter)
{
	t_complex	comp;

	x = map_mouse_to_set(x, 1, vars->box);
	y = map_mouse_to_set(y, 0, vars->box);
	comp.c_x = x;
	comp.c_y = y;
	comp.x_s = x * x;
	comp.y_s = y * y;
	comp.period = 0;
	comp.iteration = 0;
	comp.q = ((x - 0.25) * (x - 0.25)) + comp.y_s;
	if ((vars->box.x_max > 0.5 && comp.q * (comp.q + (x - 0.25))
			<= 0.25 * comp.y_s) || ((x + 1) * (x + 1)) + comp.y_s <= 0.0625)
		return (max_iter);
	comp = mandelbrot_core(comp, x, y, max_iter);
	return (comp.iteration);
}
