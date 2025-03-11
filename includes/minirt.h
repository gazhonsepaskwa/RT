/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:38:32 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 09:38:32 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>

// define
# define WIDTH 720
# define HEIGHT 480

// struct 
typedef struct s_img
{
	void		*self;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_graph
{
	void	*xsrv;
	void	*win;
	t_img	img;
	
}	t_graph;


int	mlx_put_px(t_img *img, int x, int y, int color);

#endif
