/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:21:50 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 16:21:50 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Minirt.h"
#include "../../../includes/macros.h"
#include "../../../includes/Vec.h"
#include "../../../includes/Cam.h"

static void	move_cam(int keycode, t_mrt *mrt)
{
	t_ca	*cam;
	t_v3	mv;

	mv = (t_v3){0, 0, 0, 0, 0};
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
	if (keycode == XK_z)
		mv = vec_scale (cam->up, -SPEED);
	cam->pos = vec_add(cam->pos, mv);
}

static void	move_sp(int keycode, t_mrt *mrt)
{
	t_sp	*sp;
	t_v3	mv;

	sp = mrt->obj.sh->sp;
	if (keycode == XK_w)
		mv = vec_scale(mrt->sc->cam->fw, SPEED);
	if (keycode == XK_s)
		mv = vec_scale(mrt->sc->cam->fw, -SPEED);
	if (keycode == 32)
		mv = vec_scale(mrt->sc->cam->up, SPEED);
	if (keycode == XK_z)
		mv = vec_scale(mrt->sc->cam->up, -SPEED);
	if (keycode == XK_d)
		mv = vec_scale(mrt->sc->cam->right, SPEED);
	if (keycode == XK_a)
		mv = vec_scale(mrt->sc->cam->right, -SPEED);
	sp->pos = vec_add(sp->pos, mv);
}

t_v3 rot_axis(t_v3 v, t_v3 k, float angle)
{
    float cos_theta; 
    float sin_theta; 
	t_v3	t1;
	t_v3	t2;
	t_v3	t3;
    
	cos_theta = cos(angle);
	sin_theta = sin(angle);
    k = norm(k);
    t1 = vec_scale(v, cos_theta);
    t2 = vec_scale(cross(k, v), sin_theta);
    t3 = vec_scale(k, dot(k, v) * (1 - cos_theta));
    return vec_add(vec_add(t1, t2), t3);
}

void ortho_cam(t_ca *cam)
{
	t_v3	up;

	up = (t_v3){0, 1, 0, 0, 0};
    cam->fw = norm(cam->fw);
    cam->right = norm(cross(cam->fw, up));
    cam->up = norm(cross(cam->right, cam->fw));
}

void	rotate(int keycode, t_mrt *mrt)
{
	if (keycode == XK_Down)
	{
		mrt->sc->cam->fw = rot_axis(mrt->sc->cam->fw, mrt->sc->cam->right, -0.2);
		mrt->sc->cam->up = rot_axis(mrt->sc->cam->up, mrt->sc->cam->right, -0.2);
	}
	else if (keycode == XK_Up)
	{
		mrt->sc->cam->fw = rot_axis(mrt->sc->cam->fw, mrt->sc->cam->right, 0.2);
		mrt->sc->cam->up = rot_axis(mrt->sc->cam->up, mrt->sc->cam->right, 0.2);
	}
	else if (keycode == XK_Right)
	{
		mrt->sc->cam->fw = rot_axis(mrt->sc->cam->fw, mrt->sc->cam->up, -0.2);
		mrt->sc->cam->right = rot_axis(mrt->sc->cam->right, mrt->sc->cam->up, -0.2);
	}
	else if (keycode == XK_Left)
	{
		mrt->sc->cam->fw = rot_axis(mrt->sc->cam->fw, mrt->sc->cam->up, 0.2);
		mrt->sc->cam->right = rot_axis(mrt->sc->cam->right, mrt->sc->cam->up, 0.2);
	}
	ortho_cam(mrt->sc->cam);
}

void move(int keycode, t_mrt *mrt)
{
	if (mrt->obj.type == OBJ_CAM)
		move_cam(keycode, mrt);
	if (mrt->obj.type == OBJ_SP)
		move_sp(keycode, mrt);
}
