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
#include "../../lib/libft/libft.h"
#include "../../includes/macros.h"
#include "../../includes/Vec.h"

#include <dirent.h>

static void	load_texture(t_img *img, char *path, void *xsrv)
{
	img->self = mlx_xpm_file_to_image(xsrv, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->self, &img->bpp, &img->line_len, &img->endian);
}

#include <stdio.h>
t_v3 get_nmap_vec(t_img *nmap, int x, int y, t_v3 base_n)
{
    float rgb[3];
    t_v3 col_n;
    t_v3 out;
    t_v3 axis[2];
    int px_s;

    px_s = (y * nmap->line_len + x * (nmap->bpp / 8));
    rgb[2] = (unsigned char)nmap->addr[px_s];
    rgb[1] = (unsigned char)nmap->addr[px_s + 1];
    rgb[0] = (unsigned char)nmap->addr[px_s + 2];
    // if (fabs(base_n.x) > fabs(base_n.y))
    //     axis[0] = norm(cross(base_n, (t_v3){0, 1, 0, 0, 0}));
    // else
    //     axis[0] = norm(cross(base_n, (t_v3){0, 0, 1, 0, 0}));
    // axis[1] = norm(cross(base_n, axis[0]));
	if (fabs(dot(base_n, (t_v3){1,0,0,0,0})) < EPSILON)
		axis[0] = norm(cross(base_n, (t_v3){1,0,0,0,0}));
	else
		axis[0] = norm(cross(base_n, (t_v3){0,1,0,0,0}));
	axis[1] = norm(cross(base_n, axis[0]));

	// printf("b, x %f y %f z %f\n", base_n.x,base_n.y, base_n.z);
	// printf("0, x %f y %f z %f\n", axis[0].x,axis[0].y,axis[0].z);
	// printf("1, x %f y %f z %f\n\n", axis[1].x,axis[1].y,axis[1].z);
    col_n = (t_v3){
        ((rgb[0] / 255.0f) * 2.0f) - 1.0f,
        ((rgb[1] / 255.0f) * 2.0f) - 1.0f,
        ((rgb[2] / 255.0f) * 2.0f) - 1.0f,
        0,0};
    out.x = axis[0].x * col_n.x + axis[1].x * col_n.y + base_n.x * col_n.z;
    out.y = axis[0].y * col_n.x + axis[1].y * col_n.y + base_n.y * col_n.z;
    out.z = axis[0].z * col_n.x + axis[1].z * col_n.y + base_n.z * col_n.z;
    return (norm(out));
}


void init_texture(t_texture *tex, void *xsrv, char *path)
{
	DIR 			*dir;
    struct dirent 	*entry;
	char 			*file;


	tex->existn = false;
	tex->existb = false;
	if (!path || path[ft_strlen(path) - 1] != '/')
		return ;
    dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
    while (entry != NULL)
	{
		if (ft_strnstr(entry->d_name,"base", -1))
		{
			file = ft_strjoin(path, entry->d_name);
			load_texture(&tex->b, file, xsrv);
			ft_free(&file);
			tex->existb = true;
		}
		if (ft_strnstr(entry->d_name,"normal", -1))
		{
			file = ft_strjoin(path, entry->d_name);
			load_texture(&tex->n, file, xsrv);
			ft_free(&file);
			tex->existn = true;
		}
		entry = readdir(dir);
	}
    closedir(dir);
}

float adjust_angle(float angle)
{
	while (angle > M_PI)
		angle -= 2 * M_PI;
	while (angle < -M_PI)
		angle += 2 * M_PI;
	return angle;
}

void adjust_elevation_azimuth(float *elevation, float *azimuth)
{
	if (*elevation > M_PI)
	{
		*elevation = M_PI - *elevation;
		*azimuth = adjust_angle(*azimuth + M_PI);
	}
	else if (*elevation < -M_PI)
	{
		*elevation = -M_PI - *elevation;
		*azimuth = adjust_angle(*azimuth + M_PI);
	}
}
