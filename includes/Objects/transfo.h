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

#ifndef TRANSFO_H
# define TRANSFO_H

typedef struct s_mrt	t_mrt;

void	rotate(int keycode, t_mrt *mrt);
void	move(int keycode, t_mrt *mrt);
void	scale(int btn, t_mrt *mrt);

#endif
