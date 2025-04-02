/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:28 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 12:39:28 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_addon.h"
#include "../../includes/Minirt.h"

void	draw_menu(t_mrt *mrt)
{
	if (mrt->draw_menu == true)
		mlx_put_image_to_window(mrt->g.xsrv, mrt->g.win, mrt->menu.self, 354, 0);
}
