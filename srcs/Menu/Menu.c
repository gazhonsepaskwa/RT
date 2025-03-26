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
#include "../../includes/macros.h"
#include "../../includes/Menu.h"

void	draw_menu(t_graph *g)
{
	mlx_string_put(g->xsrv, g->win, WIDTH - 80, 30, 0xffffffff, "MiniRT");
}
