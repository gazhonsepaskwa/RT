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

#include "../../includes/Objects/transfo.h"
#include "../../includes/mlx_addon.h"
#include "../../includes/Minirt.h"
#include "../../includes/macros.h"
#include "../../lib/libft/libft.h"
#include "../../includes/hook.h"

bool	is_used(int keycode, t_obj_type type)
{
	if (keycode == XK_w
		|| keycode == XK_s
		|| keycode == XK_a
		|| keycode == XK_d
		|| keycode == XK_z
		|| keycode == 32)
		return (1);
	else if (type != OBJ_LI
		&& (keycode == XK_Up
			|| keycode == XK_Down
			|| keycode == XK_Right
			|| keycode == XK_Left))
		return (1);
	return (0);
}

void	switch_light(int keycode, t_mrt *mrt)
{
	if (keycode == XK_l)
	{
		mrt->li = getlight(mrt->sc);
		mrt->obj.type = OBJ_LI;
	}
}

int	keyhook(int keycode, t_mrt *mrt)
{
	if (keycode == XK_Escape)
		close_win(mrt);
	if (keycode == XK_f)
		mrt->obj.type = OBJ_CAM;
	move(keycode, mrt);
	rotate(keycode, mrt);
	switch_light(keycode, mrt);
	if (is_used(keycode, mrt->obj.type))
		mrt->rst = true;
	return (0);
}

int	mouse_event(int button, int x, int y, t_mrt *mrt)
{
	t_ca			cam;
	float			co[2];
	t_v3			ray;
	t_curent_obj	obj;

	cam = get_cam(mrt->sc);
	co[0] = (2 * ((x + 0.5) / WIDTH) - 1) * cam.asp * cam.scale;
	co[1] = (1 - 2 * ((y + 0.5) / HEIGHT)) * cam.scale;
	ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]),
					vec_scale(cam.up, co[1])), cam.fw));
	if (button == 1)
		obj = mouse_hit_sh(ray, mrt->sc, cam.pos);
	if (button == 1 && obj.type != NOTHING)
	{
		mrt->obj = obj;
		ft_printf("=====%p=====\n", mrt->obj.sh);
		ft_printf("%d\n", mrt->obj.type);
	}
	scale(button, mrt);
	return (0);
}
