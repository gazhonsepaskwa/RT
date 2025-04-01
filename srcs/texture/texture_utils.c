/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:08:52 by lderidde          #+#    #+#             */
/*   Updated: 2025/04/01 12:08:52 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_addon.h"
#include "../../includes/texture.h"
#include "../../lib/libft/libft.h"
#include "../../includes/macros.h"
#include "../../includes/Vec.h"
#include <dirent.h>

void	init_base(char *entry, char *path, void *xsrv, t_texture *tex)
{
	char	*file;

	file = ft_strjoin(path, entry);
	load_texture(&tex->b, file, xsrv);
	ft_free(&file);
	tex->existb = true;
}

void	init_normal(char *entry, char *path, void *xsrv, t_texture *tex)
{
	char	*file;

	file = ft_strjoin(path, entry);
	load_texture(&tex->n, file, xsrv);
	ft_free(&file);
	tex->existn = true;
}
