/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:24:17 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/21 09:24:17 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_addon.h"
#include "../includes/macros.h"
#include "../lib/libft/libft.h"
#include <stdbool.h>

bool	img_init(t_graph *mlx)
{
	mlx->img[0].self = mlx_new_image(mlx->xsrv, WIDTH, HEIGHT);
	mlx->img[1].self = mlx_new_image(mlx->xsrv, WIDTH, HEIGHT);
	mlx->img[0].addr = mlx_get_data_addr(mlx->img[0].self, &mlx->img[0].bpp,
			&mlx->img[0].line_len, &mlx->img[0].endian);
	mlx->img[1].addr = mlx_get_data_addr(mlx->img[1].self, &mlx->img[1].bpp,
			&mlx->img[1].line_len, &mlx->img[1].endian);
	if (!mlx->img[0].self || !mlx->img[1].self || !mlx->img[0].addr
		|| !mlx->img[1].addr)
	{
		mlx_destroy_image(mlx->xsrv, mlx->img[0].self);
		mlx_destroy_image(mlx->xsrv, mlx->img[1].self);
		mlx_destroy_window(mlx->xsrv, mlx->win);
		mlx_destroy_display(mlx->xsrv);
		ft_free(&mlx->img[0].addr);
		ft_free(&mlx->img[1].addr);
		return (-1);
	}
	return (true);
}

int	graph_init(t_graph *mlx)
{
	mlx->xsrv = mlx_init();
	if (!mlx->xsrv)
		return (-1);
	mlx->win = mlx_new_window(mlx->xsrv, WIDTH, HEIGHT, "RayTracer");
	if (!mlx->win)
	{
		mlx_destroy_display(mlx->xsrv);
		return (-1);
	}
	if (!img_init(mlx))
	{
		mlx_destroy_display(mlx->xsrv);
		mlx_destroy_window(mlx->xsrv, mlx->win);
		return (-1);
	}
	return (0);
}
