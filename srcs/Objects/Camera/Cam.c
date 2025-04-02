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

#include "../../../lib/libft/libft.h"
#include "../../../includes/macros.h"
#include "../../../includes/Scene.h"
#include <math.h>

static	t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	return (pos);
}

t_ca	get_cam(t_sc *sc)
{
	return (*sc->cam);
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
	cam->fw = norm(init_pos(split));
	initaxis(cam->fw, &cam->up, &cam->right);
	free_tab(split);
	cam->fov = (float)ft_atoi(args[3]);
	cam->asp = (float)WIDTH / HEIGHT;
	cam->scale = tan((cam->fov * 0.35) * (M_PI / 180.0));
	return (cam);
}
