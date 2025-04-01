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
typedef struct s_li		t_li;
typedef struct s_sp		t_sp;
typedef struct s_cl		t_cl;
typedef struct s_v3		t_v3;

void	rotate(int keycode, t_mrt *mrt);
void	move(int keycode, t_mrt *mrt);
void	scale(int btn, t_mrt *mrt);

//MOVE
void	move_li(int keycode, t_li *li);
void	move_obj(int keycode, t_sp *sh);
void	move_cam(int keycode, t_mrt *mrt);

//SCALE
void	scale_sp(int btn, t_sp *sp, t_mrt *mrt);
void	scale_cl(int btn, t_cl *cl, t_mrt *mrt);
void	scale(int btn, t_mrt *mrt);

//ROTATE
void	rotate_3axis(int keycode, t_v3 *up, t_v3 *fw, t_v3 *right);

#endif
