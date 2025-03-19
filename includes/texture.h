/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:05:27 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/14 19:05:27 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include "mlx_addon.h"
#include "Color.h"	

typedef struct s_hit t_hit;
typedef struct s_v3 t_v3;
typedef struct s_sp t_sp;
typedef struct s_pl t_pl;

typedef struct s_texture
{
	t_img	b;
	t_img	n;
}			t_texture;

void	init_texture(t_texture *tex, void *xsrv, char *path);
t_v3	get_nmap_vec(t_img *nmap, int x, int y, t_v3 base_norm);
float	adjust_angle(float angle);
void	adjust_elevation_azimuth(float *elevation, float *azimuth);

// sphere
t_co 	get_sp_texture_color(t_sp *sp, t_hit hit);
t_v3	get_sp_nmap_vec(t_sp *sp, t_hit hit);

// plan
t_co	get_pl_texture_color(t_pl *pl, t_hit hit);
t_v3	get_pl_nmap_vec(t_pl *pl, t_hit hit);

#endif
