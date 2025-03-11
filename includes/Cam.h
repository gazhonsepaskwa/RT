/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:46:32 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 09:46:32 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_H
# define CAM_H

# include "Vec.h"
# include <stdlib.h>

typedef struct s_ca
{
	t_v3	pos;
	t_v3	fw;
	t_v3	up;
	t_v3	right;
	float	fov;
}	t_ca;

t_ca	*init_cam(char **args);

#endif
