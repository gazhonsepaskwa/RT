/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:33:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 10:33:41 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "Sphere.h"
# include "mlx_addon.h"
# include "Cam.h"

typedef enum e_type
{
	SPHERE,
	CAM
}	t_type;

typedef union u_sh
{
	t_sp	*sp;
	t_ca	*ca;
}	t_sh;

typedef struct s_ele
{
	t_type	type;
	t_sh	sh;
}	t_ele;

typedef struct s_sc
{
	int		nb_objs;
	t_ele	*elems;
}	t_sc;

t_ca	get_cam(t_sc *sc);
t_sc	*init_scene(char *str);

#endif
