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
	sp->col = col_from_rgb(ft_atof(split[0]),
							ft_atof(split[1]),
							ft_atof(split[2]));
	sp->vec = (t_v3){1, 0, 0, 0, 0};
	load_texture(&sp->texture, "./srcs/texture/wood/oak_veneer_01_diff_4k.xpm", xsrv);
	ft_printf("%p", sp->texture.self);
	free_tab(split);
	return (sp);
}
