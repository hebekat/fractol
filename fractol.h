/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tohebeka <tohebeka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 14:57:37 by tohebeka      #+#    #+#                 */
/*   Updated: 2022/03/25 17:58:45 by tohebeka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx/mlx.h"
# include <math.h>
# include <stdlib.h>
# define WIDTH 1000
# define HEIGTH 1000
# define MAX_ITER 100

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_rgb{
	unsigned char	r1;
	unsigned char	r2;
	unsigned char	g1;
	unsigned char	g2;
	unsigned char	b1;
	unsigned char	b2;
}				t_rgb;

typedef struct s_imgs{
	t_data		*current_img;
	t_data		img;
	t_data		img2;
	int			x;
	int			y;
	int			color;
	long double	iter;
}				t_imgs;

typedef struct s_box{
	long double	x_max;
	long double	y_max;
	long double	x_min;
	long double	y_min;
}				t_box;

typedef struct s_pal{
	int	pal[MAX_ITER];
}	t_pal;

typedef struct s_vars{
	void		*mlx;
	void		*win;
	long double	length;
	long double	zoom_level;
	t_box		box;
	t_pal		pal;
	long double	xdif;
	long double	ydif;
	int			clicking;
	int			clicked_end;
	t_data		**imgs;
}	t_vars;

typedef struct s_complex{
	long double	iteration;
	long double	c_x;
	long double	c_y;
	long double	x_s;
	long double	y_s;
	long double	log_zn;
	long double	nu;
	long double	xtemp;
	long double	q;
	int			period;
}	t_complex;

long double	mandelbrot(long double x, long double y, t_vars *vars,
				int max_iter);
long double	map_mouse_to_set(long double pos, int axis, t_box box);
int			colerp(int color1, int color2, float fraction);
t_pal		create_pallete(void);
int			mouse_clicked(int event, int mouse_x, int mouse_y, t_vars *vars);
int			reset_img(int key, t_vars *vars);
int			mouse_moved(int x, int y, t_vars *vars);
int			mouse_up(int x, int y, t_vars *vars);
void		generate_img(int mousex, int mousey, t_vars *vars);
int			generate_imgscaled(int mousex, int mousey, t_vars *vars);
t_data		**init_img(t_vars *vars);
t_imgs		swap_imgs(t_imgs imgs, t_vars *vars, int *bol);
t_pal		create_pallete(void);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		zoom(t_vars *vars, int event);

#endif
