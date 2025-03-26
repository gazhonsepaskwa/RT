/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:37:14 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 16:31:47 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_addon.h"
#include "../includes/Raytracer.h"
#include "../includes/Minirt.h"
#include "../includes/macros.h"
#include "../includes/Scene.h"
#include "../includes/check.h"
#include "../includes/hook.h"
#include "../includes/init.h"
#include <stdio.h>
#include <unistd.h>

int	render_loop(t_mrt *mrt)
{
	static int	img = 0;
	static int	l = 0;
	static int	rbs = RENDER_BOX_SIZE;

	if (mrt->rst == true)
	{
		rbs = RENDER_BOX_SIZE;
		mrt->rst = false;
		l = 0;
		render_frame(&mrt->g.img[img], RENDER_BOX_SIZE, mrt);
		mlx_put_image_to_window(mrt->g.xsrv, mrt->g.win, mrt->g.img[img].self, 0, 0);
		img = (img + 1) % 2;
		mlx_reset_img(&mrt->g.img[img]);
		return (0);
	}
	if (rbs != 1)
	{
		render_line(&mrt->g.img[img], rbs, mrt, l);
		l = (l + rbs);
		if (l > HEIGHT)
		{
			l = 0;
			rbs = rbs/2;
			mlx_put_image_to_window(mrt->g.xsrv, mrt->g.win, mrt->g.img[img].self, 0, 0);
			img = (img + 1) % 2;
			mlx_reset_img(&mrt->g.img[img]);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_mrt	mrt;

	if (!check(ac, av))
		return (1);
	if (graph_init(&mrt.g) == -1)
		return (1);
	mrt.sc = init_scene(av[1], mrt.g.xsrv);
	mrt.obj.sh = NULL;
	mrt.obj.type = OBJ_CAM;
	mrt.rst = false;
	mlx_loop_hook(mrt.g.xsrv, render_loop, &mrt);
	mlx_hook(mrt.g.win, KEYD, 1L << 0, keyhook, &mrt);
	mlx_hook(mrt.g.win, CLOSE_BTN, 0, close_win, &mrt);
	mlx_mouse_hook(mrt.g.win, &mouse_event, &mrt);
	mlx_loop(mrt.g.xsrv);
	return (0);
}
