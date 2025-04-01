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

#include "../../../includes/Objects/transfo.h"
#include "../../../includes/Objects/Cam.h"
#include "../../../includes/Minirt.h"
#include "../../../includes/Vec.h"

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

void	move(int keycode, t_mrt *mrt)
{
	if (mrt->obj.type == OBJ_CAM)
		move_cam(keycode, mrt);
	else if (mrt->obj.type == OBJ_LI)
		move_li(keycode, mrt->li);
	else
		move_obj(keycode, mrt->obj.sh);
}
