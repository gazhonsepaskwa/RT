/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:14:19 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 09:48:21 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_addon.h"
#include "../../includes/Minirt.h"
#include "../../includes/hook.h"

int	close_win(t_graph *graph)
{
	mlx_destroy_image(graph->xsrv, graph->img.self);
	mlx_destroy_window(graph->xsrv, graph->win);
	mlx_destroy_display(graph->xsrv);
	free(graph->xsrv);
	exit(EXIT_SUCCESS);
}

void move(int keycode, t_mrt *mrt)
{
	(void)mrt;
	(void)keycode;
	return ;
}

int	keyhook(int keycode, t_mrt *mrt)
{
	if (keycode == XK_Escape)
		close_win(&mrt->g);
	move(keycode, mrt);
	mlx_put_image_to_window(mrt->g.xsrv, mrt->g.win, mrt->g.img.self, 0, 0);
	return (0);
}

int mouse_event(int button, int x, int y, t_mrt *mrt)
{
	t_ca	cam;
	float	co[2];
	t_v3	ray;

	(void)button;
	cam = get_cam(mrt->sc);
	co[0] = (2 * ((x + 0.5)/WIDTH) - 1) * cam.asp * cam.scale;
	co[1] = (1 - 2 * ((y+ 0.5) / HEIGHT)) * cam.scale;
	ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]), vec_scale(cam.up, co[1])), cam.fw));
	if (hit_sh(ray, mrt->sc, cam.pos))
		ft_printf("object selected");
    return (0);
}

