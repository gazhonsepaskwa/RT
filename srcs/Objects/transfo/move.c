/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:19 by lderidde          #+#    #+#             */
/*   Updated: 2025/04/01 11:17:19 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Cam.h"
#include "../../../includes/Minirt.h"
#include "../../../includes/macros.h"
#include "../../../includes/Vec.h"

void	move_cam(int keycode, t_mrt *mrt)
{
	t_ca	*cam;
	t_v3	mv;

	mv = (t_v3){0, 0, 0, 0, 0};
	cam = mrt->sc->cam;
	if (keycode == XK_w)
		mv = vec_scale (cam->fw, SPEED);
	else if (keycode == XK_s)
		mv = vec_scale (cam->fw, -SPEED);
	else if (keycode == XK_d)
		mv = vec_scale (cam->right, SPEED);
	else if (keycode == XK_a)
		mv = vec_scale (cam->right, -SPEED);
	else if (keycode == 32)
		mv = vec_scale (cam->up, SPEED);
	else if (keycode == XK_z)
		mv = vec_scale (cam->up, -SPEED);
	cam->pos = vec_add(cam->pos, mv);
}

void	move_obj(int keycode, t_sp *sh)
{
	t_v3	mv;

	mv = (t_v3){0, 0, 0, 0, 0};
	if (keycode == XK_w)
		mv = vec_scale((t_v3){1, 0, 0, 0, 0}, SPEED);
	else if (keycode == XK_s)
		mv = vec_scale((t_v3){1, 0, 0, 0, 0}, -SPEED);
	else if (keycode == 32)
		mv = vec_scale((t_v3){0, 1, 0, 0, 0}, SPEED);
	else if (keycode == XK_z)
		mv = vec_scale((t_v3){0, 1, 0, 0, 0}, -SPEED);
	else if (keycode == XK_d)
		mv = vec_scale((t_v3){0, 0, 1, 0, 0}, SPEED);
	else if (keycode == XK_a)
		mv = vec_scale((t_v3){0, 0, 1, 0, 0}, -SPEED);
	sh->pos = vec_add(sh->pos, mv);
}

void	move_li(int keycode, t_li *li)
{
	t_v3	mv;

	mv = (t_v3){0, 0, 0, 0, 0};
	if (keycode == XK_w)
		mv = vec_scale((t_v3){1, 0, 0, 0, 0}, SPEED);
	else if (keycode == XK_s)
		mv = vec_scale((t_v3){1, 0, 0, 0, 0}, -SPEED);
	else if (keycode == 32)
		mv = vec_scale((t_v3){0, 1, 0, 0, 0}, SPEED);
	else if (keycode == XK_z)
		mv = vec_scale((t_v3){0, 1, 0, 0, 0}, -SPEED);
	else if (keycode == XK_d)
		mv = vec_scale((t_v3){0, 0, 1, 0, 0}, SPEED);
	else if (keycode == XK_a)
		mv = vec_scale((t_v3){0, 0, 1, 0, 0}, -SPEED);
	li->pos = vec_add(li->pos, mv);
}
