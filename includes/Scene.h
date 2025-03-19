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

# include "Light.h"
# include "Sphere.h"
# include "Vec.h"
# include "Plane.h"
# include "Cylinder.h"
# include "mlx_addon.h"
# include "Cam.h"

typedef enum e_type
{
	SPHERE,
	LIGHT,
	PLANE,
	CYLINDER
}	t_type;

typedef union u_sh
{
	t_sp	*sp;
	t_li	*li;
	t_pl	*pl;
	t_cl	*cl;
}	t_sh;

typedef struct s_ele
{
	t_type	type;
	t_sh	sh;
}	t_ele;

typedef struct s_sc
{
	int		nb_objs;
	int 	color;
	float	li;
	t_ca	*cam;
	t_ele	*elems;
}	t_sc;

t_ca	get_cam(t_sc *sc);
t_sc	*init_scene(char *str, void *xsrv);
t_li	*getLight(t_sc *sc);

#endif
