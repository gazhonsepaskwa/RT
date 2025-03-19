/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:42:11 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/14 14:42:11 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_addon.h"
#include "../../includes/texture.h"
#include "../../includes/Vec.h"
#include <dirent.h>

static void	load_texture(t_img *img, char *path, void *xsrv)
{
	img->self = mlx_xpm_file_to_image(xsrv, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->self, &img->bpp, &img->line_len, &img->endian);
}

t_v3 get_nmap_vec(t_img *nmap, int x, int y)
{
	float	r;
	float	g;
	float	b;
	int	px_s;

	px_s = (y * nmap->line_len + x * (nmap->bpp / 8));
	r = abs(nmap->addr[px_s]);
	g = abs(nmap->addr[px_s + 1]);
	b = abs(nmap->addr[px_s + 2]);
	if (g < 0)
		g+=256;
	if (b < 0)
		b+=256;
	if (r < 0)
		r+=256;
	return ((t_v3){((r/255) * 2) - 1,((g/255) * 2) - 1,((b/255) * 2) - 1,0,0});
}

void init_texture(t_texture *tex, void *xsrv, char *path)
{
	DIR 			*dir;
    struct dirent 	*entry;
	char 			*file;

    dir = opendir(path);
	entry = readdir(dir);
    while (entry != NULL)
	{
		if (ft_strnstr(entry->d_name,"base", -1))
		{
			file = ft_strjoin(path, entry->d_name);
			load_texture(&tex->b, file, xsrv);
			ft_free(&file);
		}
		if (ft_strnstr(entry->d_name,"normal", -1))
		{
			file = ft_strjoin(path, entry->d_name);
			load_texture(&tex->n, file, xsrv);
			ft_free(&file);
		}
		entry = readdir(dir);
	}
    closedir(dir);
}
