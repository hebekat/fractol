/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tohebeka <tohebeka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 14:40:04 by tohebeka      #+#    #+#                 */
/*   Updated: 2022/03/25 17:46:21 by tohebeka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	generate_img(int mousex, int mousey, t_vars *vars)
{
	t_imgs		imgs;
	static int	bol = 1;

	imgs.x = 0;
	imgs.y = 0;
	imgs = swap_imgs(imgs, vars, &bol);
	while (imgs.x < WIDTH)
	{
		while (imgs.y < HEIGTH)
		{
			imgs.iter = mandelbrot(imgs.x, imgs.y, vars, MAX_ITER);
			if (imgs.iter < MAX_ITER)
			{
				imgs.color = colerp(vars->pal.pal[(int) imgs.iter],
						vars->pal.pal[(int) imgs.iter + 1], fmod(imgs.iter, 1));
				my_mlx_pixel_put(imgs.current_img, imgs.x, imgs.y, imgs.color);
			}
			else
				my_mlx_pixel_put(imgs.current_img, imgs.x, imgs.y, 0x000000);
			imgs.y++;
		}
		imgs.y = 0;
		imgs.x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, imgs.current_img->img, 0, 0);
}

int	main(void)
{
	t_vars	*vars;
	t_data	**imgs;

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
	vars->clicking = 0;
	vars->clicked_end = 0;
	vars->imgs = iniz_img(vars);
	generate_img(0, 0, vars);
	mlx_mouse_hook(vars->win, mouse_clicked, vars);
	mlx_key_hook(vars->win, reset_img, vars);
	mlx_loop(vars->mlx);
}
