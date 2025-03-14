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
#include "../includes/hook.h"
#include "../includes/Menu.h"
#include "../includes/Raytracer.h"
#include "../includes/Minirt.h"
#include "../includes/macros.h"
// #include <stdio.h>

bool img_init(t_graph *mlx)
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

static int	graph_init(t_graph *mlx)
{
	mlx->xsrv = mlx_init();
	if (!mlx->xsrv)
		return (-1);
	mlx->win = mlx_new_window(mlx->xsrv, WIDTH, HEIGHT, "RayTracer");
	if (!mlx->win)
	{
		mlx_destroy_window(mlx->xsrv, mlx->win);
		mlx_destroy_display(mlx->xsrv);
		return (-1);
	}
	if (!img_init(mlx))
		return (-1);
	return (0);
}

int	render_loop(t_mrt *mrt)
{
	static int	img = 0;
	static int	rbs = RENDER_BOX_SIZE;

	if (mrt->rst == true)
	{
		rbs = RENDER_BOX_SIZE;
		img = (img + 1) % 2;
		mrt->rst = false;
	}
	if (rbs != 1)
	{
		mlx_reset_img(&mrt->g.img[img]);
		render_frame(mrt->sc, &mrt->g.img[img], rbs);
		mlx_put_image_to_window(mrt->g.xsrv, mrt->g.win, mrt->g.img[img].self, 0, 0);
		img = (img + 1) % 2;
		rbs = rbs/2;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_mrt	mrt;

	(void)ac;
	if (graph_init(&mrt.g) == -1)
		return (1);
	mrt.sc = init_scene(av[1], mrt.g.xsrv);
	mrt.obj.sh = NULL;
	mrt.obj.type = OBJ_CAM;
	mrt.rst = false;
	// printf("cam.pos.x=%f\ncam.pos.y=%f\ncam.pos.z=%f\ncam.fw.x=%f\ncam.fw.y=%f\ncam.fw.z=%f\ncam.fov=%f\n", sc->elems[0].sh.ca->pos.x, sc->elems[0].sh.ca->pos.y, sc->elems[0].sh.ca->pos.z, sc->elems[0].sh.ca->fw.x, sc->elems[0].sh.ca->fw.y, sc->elems[0].sh.ca->fw.z, sc->elems[0].sh.ca->fov);
	//mlx_put_px(&graph.img, 50, 50, 0x00FF0000);
	
	mlx_loop_hook(mrt.g.xsrv, render_loop, &mrt);
	mlx_hook(mrt.g.win, KEYD, 1L << 0, keyhook, &mrt);
	mlx_hook(mrt.g.win, CLOSE_BTN, 0, close_win, &mrt);
	mlx_mouse_hook(mrt.g.win, &mouse_event, &mrt);
	mlx_loop(mrt.g.xsrv);
	return (0);
}
