/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:37:14 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 09:37:14 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/keyhook.h"

static int	graph_init(t_graph *mlx)
{
	mlx->xsrv = mlx_init();
	if (mlx->xsrv == NULL)
		return (-1);
	mlx->win = mlx_new_window(mlx->xsrv, WIDTH, HEIGHT, "RayTracer");
	mlx->img.self = mlx_new_image(mlx->xsrv, WIDTH, HEIGHT);
	if (mlx->win == NULL || mlx->img.self == NULL)
	{
		mlx_destroy_window(mlx->xsrv, mlx->win);
		mlx_destroy_image(mlx->xsrv, mlx->img.self);
		mlx_destroy_display(mlx->xsrv);
		return (-1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.self, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	if (mlx->img.addr == NULL)
	{
		mlx_destroy_image(mlx->xsrv, mlx->img.self);
		mlx_destroy_window(mlx->xsrv, mlx->win);
		mlx_destroy_display(mlx->xsrv);
		free(mlx->xsrv);
		return (-1);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_graph	graph;

	(void)ac; (void)av;

	if (graph_init(&graph) == -1)
		return (1);
	//mlx_put_px(&graph.img, 50, 50, 0x00FF0000);
	mlx_put_image_to_window(graph.xsrv, graph.win, graph.img.self, 0, 0);
	mlx_hook(graph.win, KEYD, 1L << 0, keyhook, &graph);
	mlx_hook(graph.win, CLOSE_BTN, 0, close_win, &graph);
	mlx_loop(graph.xsrv);
	return (0);
}
