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

# include "minirt.h"

// fct
int	close_win(t_graph *graph);
int	keyhook(int keycode, t_graph *graph);

#endif
