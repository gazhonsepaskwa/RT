/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:58:30 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/25 11:58:30 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include "../../includes/Minirt.h"
#include "../../includes/Scene.h"
#include "../../includes/hook.h"
#include <stdbool.h>

int	nmin(int tmp, int *min_dst)
{
	if (tmp < *min_dst && tmp != -1)
	{
		*min_dst = tmp;
		return (1);
	}
	return (0);
}

t_curent_obj	mouse_hit_sh(t_v3 ray, t_sc *sc, t_v3 pos)
{
	int				min_dst;
	t_curent_obj	out;
	int				i;

	min_dst = 2147483647;
	out = (t_curent_obj){NOTHING, (void *)0};
	i = -1;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			if (nmin(hit_sp(ray, sc->elems[i].sh.sp, pos), &min_dst))
				out = (t_curent_obj){OBJ_SP, sc->elems[i].sh.sp};
		if (sc->elems[i].type == PLANE)
			if (nmin(hit_pl(ray, sc->elems[i].sh.pl, pos), &min_dst))
				out = (t_curent_obj){OBJ_PL, sc->elems[i].sh.pl};
		if (sc->elems[i].type == CYLINDER)
			if (nmin(hit_cl(ray, sc->elems[i].sh.cl, pos), &min_dst))
				out = (t_curent_obj){OBJ_CL, sc->elems[i].sh.cl};
		if (sc->elems[i].type == CONE)
			if (nmin(hit_cn(ray, sc->elems[i].sh.cn, pos), &min_dst))
				out = (t_curent_obj){OBJ_CN, sc->elems[i].sh.cn};
	}
	return (out);
}
