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

void	load_texture(t_img *img, char *path, void *xsrv)
{
	img->self = mlx_xpm_file_to_image(xsrv, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->self, &img->bpp, &img->line_len, &img->endian);
}

int get_color(float azi, float ele, t_img *texture)
{
	int x;
	int y;

	x = ((azi + M_PI) / (2 * M_PI)) * texture->width;
    y = ((ele + M_PI / 2) / M_PI) * texture->height;
	return (texture->addr[(y * texture->line_len + x * (texture->bpp / 8))]);
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

	return (get_color(azimuth, elevation, &sp->texture));
}
