/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiazer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:42:09 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/26 16:42:09 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_addon.h"
#include "../includes/macros.h"

static int	get_px_color(int x, int y, t_img *texture)
{
	int	px_s;

	px_s = (y * texture->line_len + x * (texture->bpp / 8));
	return (get_rgb(texture->addr[px_s],
				 texture->addr[px_s + 1],
				 texture->addr[px_s + 2]));
}

static int	addpercolor(int color1, int color2, float per)
{
	int result = 0;
	int r, g, b;

	r = ((color1 >> 16) & 0xFF) + (((color2 >> 16) & 0xFF) * per);
	if (r > 255)
		r = 255;
	g = ((color1 >> 8) & 0xFF) + (((color2 >> 8) & 0xFF) * per);
	if (g > 255)
		g = 255;
	b = (color1 & 0xFF) + ((color2 & 0xFF) * per);
	if (b > 255)
		b = 255;
	result = (r << 16) | (g << 8) | b;

	return (result);
}

void	antialiazer(t_img *img, t_img *out)
{
	int	x;
	int	y;
	int	col; 

	y = 0;
	while (++y < HEIGHT - 1)
	{
		x = 0;
		while (++x < WIDTH - 1)
		{
			col = 0;
			col = addpercolor(col, get_px_color(x - 1, y - 1, img), 1.0 /36);
			col = addpercolor(col, get_px_color(x    , y - 1, img), 5.0 /36);
			// col = addpercolor(col, get_px_color(x + 1, y - 1, img), 1.0 /49);
			col = addpercolor(col, get_px_color(x - 1, y    , img), 5.0 /36);
			col = addpercolor(col, get_px_color(x    , y    , img), 25.0/36);
			// col = addpercolor(col, get_px_color(x + 1, y    , img), 5.0 /49);
			// col = addpercolor(col, get_px_color(x - 1, y + 1, img), 1.0 /49);
			// col = addpercolor(col, get_px_color(x    , y + 1, img), 5.0 /49);
			// col = addpercolor(col, get_px_color(x + 1, y + 1, img), 1.0 /49);
			mlx_put_px(out, x, y, col);
		}
	}
}
