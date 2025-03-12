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

#include "../../includes/Scene.h"
#include <math.h>
#include "../../lib/libft/libft.h"

static	t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	return (pos);
}

static t_v3	init_up(void)
{
	t_v3	up;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	return (up);
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
	cam->fw = init_pos(split);
	free_tab(split);
	cam->fov = (float)ft_atoi(args[3]);
	cam->asp = (float)WIDTH / HEIGHT;
	cam->scale = tan((cam->fov * 0.5) * (M_PI / 180.0));
	cam->fw = norm(cam->fw);
	cam->up = init_up();
	cam->right = norm(cross(cam->fw, cam->up));
	cam->up = norm(cross(cam->right, cam->fw));
	return (cam);
}
