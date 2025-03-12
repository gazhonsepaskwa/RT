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
#include "../../includes/macros.h"

int	close_win(t_graph *graph)
{
	mlx_destroy_image(graph->xsrv, graph->img[0].self);
	mlx_destroy_image(graph->xsrv, graph->img[1].self);
	mlx_destroy_window(graph->xsrv, graph->win);
	mlx_destroy_display(graph->xsrv);
	free(graph->xsrv);
	exit(EXIT_SUCCESS);
}

void move(int keycode, t_mrt *mrt)
{
	t_ca	*cam;
	t_v3	mv;

	mv.x = 0;
	mv.y = 0;
	mv.z = 0;
	cam = mrt->sc->cam;
	if (keycode == XK_w)
		mv = vec_scale (cam->fw, SPEED);
	if (keycode == XK_s)
		mv = vec_scale (cam->fw, -SPEED);
	if (keycode == XK_d)
		mv = vec_scale (cam->right, SPEED);
	if (keycode == XK_a)
		mv = vec_scale (cam->right, -SPEED);
	if (keycode == 32)
		mv = vec_scale (cam->up, SPEED);
	if (keycode == XK_Shift_L)
		mv = vec_scale (cam->up, -SPEED);
	cam->pos = vec_add(cam->pos, mv);
	
	return ;
}

void rotate(int keycode, t_mrt *mrt)
{
	if (keycode == XK_Down)
	{
		mrt->sc->cam->fw = rot_z(mrt->sc->cam->fw, 0.2);
		mrt->sc->cam->right = rot_z(mrt->sc->cam->right, 0.2);
		mrt->sc->cam->up = rot_z(mrt->sc->cam->up, 0.2);
	}
	if (keycode == XK_Up)
	{
		mrt->sc->cam->fw = rot_z(mrt->sc->cam->fw, -0.2);
		mrt->sc->cam->right = rot_z(mrt->sc->cam->right, -0.2);
		mrt->sc->cam->up = rot_z(mrt->sc->cam->up, -0.2);
	}
	if (keycode == XK_Right)
	{
		mrt->sc->cam->fw = rot_y(mrt->sc->cam->fw, 0.2);
		mrt->sc->cam->right = rot_y(mrt->sc->cam->right, 0.2);
		mrt->sc->cam->up = rot_y(mrt->sc->cam->up, 0.2);
	}
	if (keycode == XK_Left)
	{
		mrt->sc->cam->fw = rot_y(mrt->sc->cam->fw, -0.2);
		mrt->sc->cam->right = rot_y(mrt->sc->cam->right, -0.2);
		mrt->sc->cam->up = rot_y(mrt->sc->cam->up, -0.2);
	}
}

int	keyhook(int keycode, t_mrt *mrt)
{
	static int i = 1;

	if (keycode == XK_Escape)
		close_win(&mrt->g);
	move(keycode, mrt);
	rotate(keycode, mrt);
	mlx_reset_img(&mrt->g.img[i]);
	raytrace(mrt->sc, &mrt->g.img[i]);
	mlx_put_image_to_window(mrt->g.xsrv, mrt->g.win, mrt->g.img[i].self, 0, 0);
	i = (i + 1) % 2;
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
	ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]),
							vec_scale(cam.up, co[1])), cam.fw));
	if (hit_sh(ray, mrt->sc, cam.pos))
		ft_printf("object selected; no effect for now\n");
    return (0);
}

