/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_adon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:03:11 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 10:03:11 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_addon.h"
#include "../../includes/macros.h"

int	mlx_put_px(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return (-1);
	pixel = img->addr + ((y * img->line_len) + (x * (img->bpp / 8)));
	*(unsigned int *)pixel = color;
	return (0);
}

void	mlx_put_rect(t_img* img, t_xy pt1, t_xy pt2, int color)
{
	int	x;
	int	y;

	y = pt1.y;
	while (y < pt2.y)
	{
		x = pt1.x;
		while(x < pt2.x)
		{
			mlx_put_px(img, x, y, color);
			++x;
		}
		++y;
	}
}

int	col_from_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int get_rgb(int r, int g, int b)
{
	if (g < 0)
		g+=256;
	if (b < 0)
		b+=256;
	if (r < 0)
		r+=256;
    return (abs(b) << 16 | abs(g) << 8 | abs(r));
}

void	mlx_reset_img(t_img *img)
{
	ft_memset(img->addr, 0, img->line_len * HEIGHT);
}
