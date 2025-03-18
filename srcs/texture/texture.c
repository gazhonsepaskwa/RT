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

#include "../../includes/Sphere.h"
#include "../../includes/Raytracer.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void	load_texture(t_img *img, char *path, void *xsrv)
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

void init_texture(t_texture *tex, char **args, void *xsrv, char *path)
{
	DIR *dir;
    struct dirent *entry;
	char *file;

	(void)tex;
	(void)args;
	(void)xsrv;
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




   /////////////////////
  // sphere specific //
 /////////////////////


static float adjust_angle(float angle)
{
	while (angle > M_PI)
		angle -= 2 * M_PI;
	while (angle < -M_PI)
		angle += 2 * M_PI;
	return angle;
}

static void adjust_elevation_azimuth(float *elevation, float *azimuth)
{
	if (*elevation > M_PI / 2)
	{
		*elevation = M_PI - *elevation;
		*azimuth = adjust_angle(*azimuth + M_PI);
	}
	else if (*elevation < -M_PI / 2)
	{
		*elevation = -M_PI - *elevation;
		*azimuth = adjust_angle(*azimuth + M_PI);
	}
}

static int get_rgb(int r, int g, int b)
{
	if (g < 0)
		g+=256;
	if (b < 0)
		b+=256;
	if (r < 0)
		r+=256;
    return (abs(b) << 16 | abs(g) << 8 | abs(r));
}

static int get_color(float azi, float ele, t_img *texture)
{
	int	x;
	int	y;
	int	px_s;

	x = ((azi + M_PI) / (2 * M_PI)) * texture->width;
    y = ((ele + M_PI / 2) / M_PI) * texture->height;
	px_s = (y * texture->line_len + x * (texture->bpp / 8));
	return (get_rgb(texture->addr[px_s], texture->addr[px_s + 1], texture->addr[px_s + 2]));
}

int get_sp_texture_color(t_sp *sp, t_hit hit)
{
    t_v3 hit_vec;
    float elevation;
    float azimuth;

    hit_vec = norm(vec_sub(hit.ori, sp->pos));
    elevation = asin(hit_vec.z) - asin(sp->vec.z);
    azimuth = atan2(hit_vec.y, hit_vec.x) - atan2(sp->vec.y, sp->vec.x);
    adjust_elevation_azimuth(&elevation, &azimuth);
    azimuth = adjust_angle(azimuth);

	return (get_color(azimuth, elevation, &sp->tex.b));
}

t_v3	get_sp_nmap_vec(t_sp *sp, t_hit hit)
{
	t_v3	tmp_vec;
    float	elevation;
    float	azimuth;
	int		x;
	int		y;

    tmp_vec = norm(vec_sub(hit.ori, sp->pos));
    elevation = asin(tmp_vec.z) - asin(sp->vec.z);
    azimuth = atan2(tmp_vec.y, tmp_vec.x) - atan2(sp->vec.y, sp->vec.x);
    adjust_elevation_azimuth(&elevation, &azimuth);
    azimuth = adjust_angle(azimuth);
	x = ((azimuth + M_PI) / (2 * M_PI)) * sp->tex.n.width;
    y = ((elevation + M_PI / 2) / M_PI) * sp->tex.n.height;
	tmp_vec = get_nmap_vec(&sp->tex.n, x, y);
    elevation = asin(tmp_vec.z) - asin(sp->vec.z);
    azimuth = atan2(tmp_vec.y, tmp_vec.x) - atan2(sp->vec.y, sp->vec.x);
    adjust_elevation_azimuth(&elevation, &azimuth);
    azimuth = adjust_angle(azimuth);
	rot_x(tmp_vec, azimuth);
	rot_y(tmp_vec, elevation);
	return (tmp_vec);
}
