/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:14:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 10:14:25 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "Vec.h"
# include <stdlib.h>

typedef struct s_sp
{
	t_v3	pos;
	float	dia;
}	t_sp;

t_sp	*init_sphere(char **args);

#endif
