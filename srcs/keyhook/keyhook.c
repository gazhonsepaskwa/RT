/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:14:19 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 10:14:19 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	close_win(t_graph *graph)
{
	mlx_destroy_image(graph->xsrv, graph->img.self);
	mlx_destroy_window(graph->xsrv, graph->win);
	mlx_destroy_display(graph->xsrv);
	free(graph->xsrv);
	exit(EXIT_SUCCESS);
}

int	keyhook(int keycode, t_graph *graph)
{
	if (keycode == XK_Escape)
		close_win(graph);
	mlx_put_image_to_window(graph->xsrv, graph->win, graph->img.self, 0, 0);
	return (0);
}
