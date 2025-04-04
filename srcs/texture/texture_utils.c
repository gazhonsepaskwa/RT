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

#include "../../includes/texture.h"
#include "../../lib/libft/libft.h"
#include <dirent.h>

void	init_base(char *entry, char *path, void *xsrv, t_texture *tex)
{
	char	*file;

	file = ft_strjoin(path, entry);
	if (file && access(file, F_OK | R_OK) == 0)
	{
		load_texture(&tex->b, file, xsrv);
		tex->existb = true;
	}
	ft_free(&file);
}

void	init_normal(char *entry, char *path, void *xsrv, t_texture *tex)
{
	char	*file;

	file = ft_strjoin(path, entry);
	if (file && access(file, F_OK | R_OK) == 0)
	{
		load_texture(&tex->n, file, xsrv);
		tex->existn = true;
	}
	ft_free(&file);
}
