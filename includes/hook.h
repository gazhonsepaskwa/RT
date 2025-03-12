/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:15:15 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 10:15:15 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef KEYHOOK_H
# define KEYHOOK_H

// define 
# define CLOSE_BTN 17
# define KEYD 2 

# include "mlx_addon.h"
#include "Raytracer.h"
#include "Minirt.h"

// fct
int		close_win(t_graph *graph);
int		keyhook(int keycode, t_mrt *mrt);
int		mouse_event(int button, int x, int y, t_mrt *mrt);
bool	hit_sh(t_v3 ray, t_sc *sc, t_v3 pos);

#endif
