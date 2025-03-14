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

#include "Sphere.h"
#include "Raytracer.h"

int get_sp_texture_color(t_sp *sp, t_hit hit);
void	load_texture(t_img *img, char *path, void *xsrv);

#endif
