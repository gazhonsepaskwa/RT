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

#include "mlx_addon.h"
#include "Scene.h"

typedef struct s_mrt
{
	t_graph	g;
	t_sc	*sc;
}			t_mrt;

#endif
