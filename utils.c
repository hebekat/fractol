/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tohebeka <tohebeka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:36:31 by tohebeka      #+#    #+#                 */
/*   Updated: 2022/03/25 17:57:32 by tohebeka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_pal	create_pallete(void)
{
	t_pal	pal;
	int		i;
	int		color;
	int		color1;
	int		color2;

	color = 0x000000;
	i = 0;
	while (i < MAX_ITER)
	{
		pal.pal[i] = colerp(0x000000, 0x0A66FC, sin(i) / 2);
		i++;
	}
	return (pal);
}

t_imgs	swap_imgs(t_imgs imgs, t_vars *vars, int *bol)
{
	if (bol)
	{
		imgs.current_img = vars->imgs[0];
		*bol = 0;
	}
	else
	{
		imgs.current_img = vars->imgs[1];
		*bol = 1;
	}
	return (imgs);
}

t_data	**init_img(t_vars *vars)
{
	t_data	**imgs;

	imgs = malloc(sizeof(t_data *) * 2);
	imgs[0] = malloc(sizeof(t_data));
	imgs[0]->img = mlx_new_image(vars->mlx, WIDTH, HEIGTH);
	imgs[0]->addr = mlx_get_data_addr(imgs[0]->img, &imgs[0]->bits_per_pixel,
			&imgs[0]->line_length, &imgs[0]->endian);
	imgs[1] = malloc(sizeof(t_data));
	imgs[1]->img = mlx_new_image(vars->mlx, WIDTH, HEIGTH);
	imgs[1]->addr = mlx_get_data_addr(imgs[1]->img,
			&imgs[1]->bits_per_pixel, &imgs[1]->line_length, &imgs[1]->endian);
	return (imgs);
}

void	init_vars(t_vars *vars)
{
	vars = malloc(sizeof(t_vars));
	vars->pal = create_pallete();
	vars->length = 4;
	vars->zoom_level = 0.3;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGTH, "fratc0l");
	vars->box.x_max = vars->length;
	vars->box.x_min = -vars->length;
	vars->box.y_max = vars->length;
	vars->box.y_min = -vars->length;
	vars->imgs = iniz_img(vars);
}
