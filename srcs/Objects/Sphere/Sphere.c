/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:16:26 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 10:16:26 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Sphere.h"
#include "../../../includes/mlx_addon.h"
#include "../../../lib/libft/libft.h"
#include "../../../includes/texture.h"

static	t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	return (pos);
}

// t_v3	rand_pt(t_li *sp)
// {
// 	t_v3	ret;
// 	float	theta;
// 	float	phi;
// 	float	x;
// 	float	y;
//
// 	x = (float)rand() / 2147483647.0f;
// 	y = (float)rand() / 2147483647.0f;
// 	theta = 2.0 * M_PI * x;
// 	phi = acos(2.0 * y - 1.0);
// 	ret.x = sp->r * sin(phi) * cos(theta);
// 	ret.y = sp->r / 2.0f * sin(phi) * sin(theta);
// 	ret.z = sp->r / 2.0f * cos(phi);
// 	ret.x = sp->pos.x + ret.x;
// 	ret.y = sp->pos.y + ret.y;
// 	ret.z = sp->pos.z + ret.z;
// 	return (ret);
// }

t_sp	*init_sphere(char **args, void *xsrv)
{
	t_sp	*sp;
	char	**split;

	sp = malloc(sizeof(t_sp) * 1);
	if (!sp)
		return (NULL);
	split = ft_split(args[1], ",");
	if (!split)
		return(free(sp), NULL);
	sp->pos = init_pos(split);
	free_tab(split);
	sp->dia = ft_atof(args[2]);
	split = ft_split(args[3], ",");
	if (!split)
		return(free(sp), NULL);
	sp->ma.col = col_from_rgb(ft_atof(split[0]),
							ft_atof(split[1]),
							ft_atof(split[2]));
	sp->ma.ka = ft_atof(args[4]);
	sp->ma.kd = ft_atof(args[5]);
	sp->ma.ks = ft_atof(args[6]);
	sp->ma.n = ft_atof(args[7]);
	sp->vec = (t_v3){1, 0, 0, 0, 0};
	init_texture(&sp->tex, args, xsrv, args[8]);
	free_tab(split);
	return (sp);
}
