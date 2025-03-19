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

#include "../../includes/Menu.h"
#include "../../includes/macros.h"

void	draw_menu(t_graph *g)
{
	t_xy tl;
	t_xy br;

	tl.x = WIDTH - 110;
	tl.y = 10;
	br.x = WIDTH - 10;
	br.y = HEIGHT - 10;
	// mlx_put_rect(&g->img, tl, br, 0x00a8a8a8);
	// mlx_put_image_to_window(g->xsrv, g->win, g->img.self, 0, 0);
	mlx_string_put(g->xsrv, g->win, WIDTH - 80, 30, 0xffffffff, "MiniRT");
}
