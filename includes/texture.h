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

#include "Raytracer.h"

typedef struct s_texture
{
	t_img	b;
	t_img	n;
}			t_texture;

int 	get_sp_texture_color(t_sp *sp, t_hit hit);
void	load_texture(t_img *img, char *path, void *xsrv);
void	init_texture(t_texture *tex, void *xsrv, char *path);
t_v3	get_sp_nmap_vec(t_sp *sp, t_hit hit);

#endif
