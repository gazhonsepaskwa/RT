/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:33:25 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 08:33:25 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "Scene.h"
# include "mlx_addon.h"

void	raytrace(t_sc *sc, t_img *img);

#endif
