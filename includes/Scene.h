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

# include "Objects/Cone.h"
# include "Objects/Cylinder.h"
# include "Objects/Sphere.h"
# include "Objects/Light.h"
# include "Objects/Plane.h"
# include "Objects/Cam.h"

typedef enum e_type
{
	SPHERE,
	LIGHT,
	PLANE,
	CONE,
	CYLINDER
}	t_type;

typedef union u_sh
{
	t_sp	*sp;
	t_pl	*pl;
	t_cl	*cl;
	t_cn	*cn;
}	t_sh;

typedef struct s_ele
{
	t_type	type;
	t_sh	sh;
}	t_ele;

typedef struct s_sc
{
	int		nb_objs;
	int		nb_lig;
	t_li	**lig;
	t_co	col;
	float	li;
	t_ca	*cam;
	t_ele	*elems;
	t_sp	hdri;
}	t_sc;

t_ca	get_cam(t_sc *sc);
t_sc	*init_scene(char *str, void *xsrv);
t_li	*getLight(t_sc *sc);
int		init_objp0(char **split, t_sc *sc, int i[2], void *xsrv);

#endif
