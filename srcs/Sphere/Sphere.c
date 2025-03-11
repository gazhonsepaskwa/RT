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

#include "../../includes/Sphere.h"
#include "../../lib/libft/libft.h"

static	t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = (float)ft_atoi(split[0]);
	pos.y = (float)ft_atoi(split[1]);
	pos.z = (float)ft_atoi(split[2]);
	return (pos);
}

t_sp	*init_sphere(char **args)
{
	t_sp	*sphere;
	char	**split;

	sphere = malloc(sizeof(t_sp) * 1);
	if (!sphere)
		return (NULL);
	split = ft_split(args[1], ",");
	if (!split)
		return(free(sphere), NULL);
	sphere->pos = init_pos(split);
	free_tab(split);
	sphere->dia = (float)ft_atoi(args[2]);
	return (sphere);
}
