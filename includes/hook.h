/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:15:15 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 16:30:12 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# define CLOSE_BTN 17
# define KEYD 2 

# include "Scene.h"

# include <stdbool.h>

typedef struct s_curent_obj		t_curent_obj;
typedef struct s_graph			t_graph;
typedef struct s_mrt			t_mrt;
typedef struct s_v3				t_v3;
typedef struct s_sc				t_sc;

int				close_win(t_mrt *mrt);
void			free_sc(t_sc *sc, void *xsrv, int sc_lim, int li_lim);
void			clean_win(t_mrt *mrt);
int				keyhook(int keycode, t_mrt *mrt);
int				mouse_event(int button, int x, int y, t_mrt *mrt);
t_curent_obj	mouse_hit_sh(t_v3 ray, t_sc *sc, t_v3 pos);

//HIT SHAPE
float			hit_sp(t_v3 ray, t_sp *sp, t_v3 cam_pos);
float			hit_pl(t_v3 ray, t_pl *pl, t_v3	cam_pos);
float			hit_cl(t_v3 ray, t_cl *cl, t_v3 cam_pos);
float			hit_cn(t_v3 ray, t_cn *cn, t_v3 cam_pos);
#endif
