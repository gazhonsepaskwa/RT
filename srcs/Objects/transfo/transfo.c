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

#include "../../../includes/Objects/Cam.h"
#include "../../../includes/Minirt.h"
#include "../../../includes/macros.h"
#include "../../../includes/Vec.h"


  //////////
 // move //
//////////

static void	move_cam(int keycode, t_mrt *mrt)
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

static void	move_obj(int keycode, t_sp *sh)
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

static void	move_li(int keycode, t_li *li)
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





  ////////////
 // rotate //
////////////

static t_v3 rot_axis(t_v3 v, t_v3 k, float angle)
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
    return norm(vec_add(vec_add(t1, t2), t3));
}

void	rotate_3axis(int keycode, t_v3 *up, t_v3 *fw, t_v3 *right)
{
	t_v3	tmp;

	tmp = (t_v3){0,1,0,0,0};
	if (keycode == XK_Down)
	{
		*fw = rot_axis(*fw, *right, -M_PI/32);
		*up = rot_axis(*up, *right, -M_PI/32);
	}
	else if (keycode == XK_Up)
	{
		*fw = rot_axis(*fw, *right, M_PI/32);
		*up = rot_axis(*up, *right, M_PI/32);
	}
	else if (keycode == XK_Right)
	{
		if (fabs(dot(*fw, tmp)) > EPSILON)
			tmp = (t_v3){1,0,0,0,0};
		*fw = rot_axis(*fw, tmp, -M_PI/32);
		*right = norm(cross(*fw, tmp));
		*up = norm(cross(*right, *fw));
	}
	else if (keycode == XK_Left)
	{
		if (fabs(dot(*fw, tmp)) > EPSILON)
			tmp = (t_v3){1,0,0,0,0};
		*fw = rot_axis(*fw, tmp, M_PI/32);
		*right = norm(cross(*fw, tmp));
		*up = norm(cross(*right, *fw));
	}
}






  ///////////
 // scale //
///////////

void	scale_sp(int btn, t_sp *sp, t_mrt *mrt)
{
	if ((btn != 4 && btn != 5) || (btn == 5 && sp->dia <= 0.5))
		return ;
	if (btn == 4)
		sp->dia += 0.2; 
	if (btn == 5)
		sp->dia -= 0.2; 
	mrt->rst = true;
}

void	scale_cl(int btn, t_cl *cl, t_mrt *mrt)
{
	if ((btn != 4 && btn != 5 && btn != 6 && btn != 7)
	|| (btn == 5 && cl->h <= 0.5)
	|| (btn == 7 && cl->r <= 0.5))
		return ;
	if (btn == 4)
		cl->h += 0.2;
	if (btn == 5)
		cl->h -= 0.2;
	if (btn == 6)
		cl->r += 0.2;
	if (btn == 7)
		cl->r -= 0.2;
	mrt->rst = true;
}






  //////////
 // main //
//////////

void	scale(int btn, t_mrt *mrt)
{
	if (mrt->obj.type == OBJ_SP)
		scale_sp(btn, mrt->obj.sh, mrt);
	if (mrt->obj.type == OBJ_CL)
		scale_cl(btn, mrt->obj.sh, mrt);
	if (mrt->obj.type == OBJ_LI)
	{
		if (mrt->li->li < 0.95 && btn == 4)
			mrt->li->li += 0.05;
		if (mrt->li->li > 0.05 && btn == 5)
			mrt->li->li -= 0.05;
		mrt->rst = true;
	}
}

void	rotate(int keycode, t_mrt *mrt)
{
	if (mrt->obj.type == OBJ_CAM)
		rotate_3axis(keycode, &mrt->sc->cam->up, &mrt->sc->cam->fw,
			&mrt->sc->cam->right);
	if (mrt->obj.type == OBJ_SP)
		rotate_3axis(keycode, &((t_sp *)mrt->obj.sh)->up,
			&((t_sp *)mrt->obj.sh)->fw, &((t_sp *)mrt->obj.sh)->ri);
	if (mrt->obj.type == OBJ_CL)
		rotate_3axis(keycode, &((t_cl *)mrt->obj.sh)->norm,
			&((t_cl *)mrt->obj.sh)->fw, &((t_cl *)mrt->obj.sh)->ri);
	if (mrt->obj.type == OBJ_CN)
		rotate_3axis(keycode, &((t_cn *)mrt->obj.sh)->norm,
			&((t_cn *)mrt->obj.sh)->fw, &((t_cn *)mrt->obj.sh)->ri);
	if (mrt->obj.type == OBJ_PL)
		rotate_3axis(keycode, &((t_pl *)mrt->obj.sh)->norm,
			&((t_pl *)mrt->obj.sh)->x, &((t_pl *)mrt->obj.sh)->y);

}

void move(int keycode, t_mrt *mrt)
{
	if (mrt->obj.type == OBJ_CAM)
		move_cam(keycode, mrt);
	else if (mrt->obj.type == OBJ_LI)
		move_li(keycode, mrt->li);
	else
		move_obj(keycode, mrt->obj.sh);
}
