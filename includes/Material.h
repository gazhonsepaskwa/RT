/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:04:28 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/17 09:04:28 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

typedef struct s_mat
{
	int		col;
	float	ka;
	float	kd;
	float	ks;
	float	n;
	float	c[3];
}	t_mat;

#endif
