/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:11:56 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/18 14:11:56 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Light.h"
#include "../../../lib/libft/libft.h"

static t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	return (pos);
}

t_co	init_color(char **arg)
{
	t_co	col;

	col.r = ft_atof(arg[0]) / 255;
	col.g = ft_atof(arg[1]) / 255;
	col.b = ft_atof(arg[2]) / 255;
	return (col);
}

static t_co	init_lcolor(t_li *li, char **arg)
{
	t_co	col;

	col.r = ft_atof(arg[0]) / 255.0 * li->li;
	col.g = ft_atof(arg[1]) / 255.0 * li->li;
	col.b = ft_atof(arg[2]) / 255.0 * li->li;
	return (col);
}

t_li	*init_light(char **split)
{
	t_li	*li;
	char	**arg;

	li = malloc(sizeof(t_li) * 1);
	if (!li)
		return (NULL);
	arg = ft_split(split[1], ",");
	if (!arg)
		return (free(li), NULL);
	li->pos = init_pos(arg);
	free_tab(arg);
	li->li = ft_atof(split[2]);
	li->r = 0.5f;
	arg = ft_split(split[3], ",");
	if (!arg)
		return (free(li), NULL);
	li->col = init_lcolor(li, arg);
	free_tab(arg);
	return (li);
}
