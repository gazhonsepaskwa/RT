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

# include "Scene.h"

# include <stdbool.h>

typedef enum e_obj_type
{
	OBJ_CAM,
	OBJ_SP
}	t_obj_type;

typedef struct s_curent_obj
{
	t_obj_type	type;
	t_sh		*sh;
}				t_curent_obj;

typedef struct s_mrt
{
	t_graph			g;
	t_sc			*sc;
	t_curent_obj	obj;
	bool			rst;
}					t_mrt;

#endif
