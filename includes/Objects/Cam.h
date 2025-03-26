/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:46:32 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 16:30:23 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_H
# define CAM_H

# include "../Vec.h"

typedef struct s_sc	t_sc;

typedef struct s_ca
{
	t_v3	pos;
	t_v3	fw;
	t_v3	up;
	t_v3	right;
	float	fov;
	float	scale;
	float	asp;
}	t_ca;

t_ca	*init_cam(char **args);
t_ca	get_cam(t_sc *sc);

#endif
