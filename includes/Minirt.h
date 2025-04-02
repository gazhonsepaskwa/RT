/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:47:56 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 08:47:56 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx_addon.h"
# include "Scene.h"
# include <stdbool.h>

typedef enum e_obj_type
{
	NOTHING,
	OBJ_CAM,
	OBJ_SP,
	OBJ_CN,
	OBJ_PL,
	OBJ_CL,
	OBJ_LI
}	t_obj_type;

typedef struct s_curent_obj
{
	t_obj_type	type;
	void		*sh;
}				t_curent_obj;

typedef struct s_mrt
{
	t_graph			g;
	t_sc			*sc;
	t_curent_obj	obj;
	t_li			*li;
	bool			rst;
	bool			draw_menu;
	t_img			menu;
}					t_mrt;

#endif
