/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:25:00 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 16:25:00 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSPHO_H
# define TRANSPHO_H

#include "Minirt.h"

void move(int keycode, t_mrt *mrt);
void rotate(int keycode, t_mrt *mrt);

#endif
