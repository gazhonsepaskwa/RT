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

#include "../includes/mlx_addon.h"
#include "../includes/Scene.h"
#include "../includes/keyhook.h"
#include "../includes/Menu.h"
#include <stdio.h>

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
	t_sc	*sc;

	(void)ac;

	if (graph_init(&graph) == -1)
		return (1);
	sc = init_scene(av[1]);
	// printf("cam.pos.x=%f\ncam.pos.y=%f\ncam.pos.z=%f\ncam.fw.x=%f\ncam.fw.y=%f\ncam.fw.z=%f\ncam.fov=%f\n", sc->elems[0].sh.ca->pos.x, sc->elems[0].sh.ca->pos.y, sc->elems[0].sh.ca->pos.z, sc->elems[0].sh.ca->fw.x, sc->elems[0].sh.ca->fw.y, sc->elems[0].sh.ca->fw.z, sc->elems[0].sh.ca->fov);
	//mlx_put_px(&graph.img, 50, 50, 0x00FF0000);
	
	draw_menu(&graph);
	
	mlx_hook(graph.win, KEYD, 1L << 0, keyhook, &graph);
	mlx_hook(graph.win, CLOSE_BTN, 0, close_win, &graph);
	mlx_loop(graph.xsrv);
	return (0);
}
