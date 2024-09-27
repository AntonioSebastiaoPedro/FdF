/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:58 by ansebast          #+#    #+#             */
/*   Updated: 2024/09/27 16:20:12 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
        int     i;
        int     j;
        
        i = 5;
        j = 5;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 920, "Ansebast's FDF");
	img.img = mlx_new_image(mlx, 1920, 920);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
        while (i < 2000)
        {
                while (j <= 600)
                {
                        if (i >= 5 && i <= 500)
                                my_mlx_pixel_put(&img, i, j, 0x0000FF00);
                        else if (i > 500 && i <= 1000)
                                my_mlx_pixel_put(&img, i, j, 0x00FF0000);
                        else if (i > 1000 && i <= 1500)
                                my_mlx_pixel_put(&img, i, j, 0xFF000000);
                        else if (i > 1500 && i <= 2000)
                                my_mlx_pixel_put(&img, i, j, 0xFFFFFF00);
                        j++;
                }
                i++;
                j = 5;
        }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
