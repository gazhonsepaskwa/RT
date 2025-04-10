/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_addon.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:38:32 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 12:22:48 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ADDON_H
# define MLX_ADDON_H

# include "../lib/mlx/mlx.h"

# include <X11/keysym.h>

typedef struct s_img
{
	void		*self;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_graph
{
	void	*xsrv;
	void	*win;
	t_img	img[2];
}	t_graph;

typedef struct s_xy
{
	float	x;
	float	y;
}	t_xy;

void	mlx_put_rect(t_img *img, t_xy pt1, t_xy pt2, int color);
void	mlx_reset_img(t_img *img);

int		mlx_put_px(t_img *img, int x, int y, int color);
int		col_from_rgb(int r, int g, int b);
int		get_rgb(int r, int g, int b);

#endif
