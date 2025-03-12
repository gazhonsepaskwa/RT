/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:57:46 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/12 08:57:46 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"

t_hit	init_hit(t_v3 ray)
{
	t_hit	hit;

	hit.hit = false;
	hit.ray = ray;
	return (hit);
}
