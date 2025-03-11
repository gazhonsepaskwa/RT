/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:58:28 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 09:58:28 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cam.h"
#include "../../lib/libft/libft.h"

static	t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = (float)ft_atoi(split[0]);
	pos.y = (float)ft_atoi(split[1]);
	pos.z = (float)ft_atoi(split[2]);
	return (pos);
}

t_ca	*init_cam(char **args)
{
	t_ca	*cam;
	char	**split;

	cam = malloc(sizeof(t_ca) * 1);
	if (!cam)
		return (NULL);
	split = ft_split(args[1], ",");
	if (!split)
		return (free(cam), NULL);
	cam->pos = init_pos(split);
	free_tab(split);
	split = ft_split(args[2], ",");
	if (!split)
		return (free(cam), NULL);
	cam->fw = init_pos(split);
	free_tab(split);
	cam->fov = (float)ft_atoi(args[3]);
	return (cam);
}
