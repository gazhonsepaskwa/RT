/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:37:14 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 09:37:14 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_addon.h"
#include "../includes/Scene.h"
#include "../includes/keyhook.h"
#include "../includes/Menu.h"
#include <stdio.h>

static int	graph_init(t_graph *mlx)
{
	mlx->xsrv = mlx_init();
	if (mlx->xsrv == NULL)
		return (-1);
	mlx->win = mlx_new_window(mlx->xsrv, WIDTH, HEIGHT, "RayTracer");
	mlx->img.self = mlx_new_image(mlx->xsrv, WIDTH, HEIGHT);
	if (mlx->win == NULL || mlx->img.self == NULL)
	{
		mlx_destroy_window(mlx->xsrv, mlx->win);
		mlx_destroy_image(mlx->xsrv, mlx->img.self);
		mlx_destroy_display(mlx->xsrv);
		return (-1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.self, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	if (mlx->img.addr == NULL)
	{
		mlx_destroy_image(mlx->xsrv, mlx->img.self);
		mlx_destroy_window(mlx->xsrv, mlx->win);
		mlx_destroy_display(mlx->xsrv);
		free(mlx->xsrv);
		return (-1);
	}
	return (0);
}

#include <stdbool.h>
float	second_degree(float a, float b, float c, bool pos)
{
	float delta;

	delta = powf(b, 2) - (4 * a * c);
	if (pos)
		return (((b * -1) + sqrt(delta)) / (2 * a));
	else
		return (((b * -1) - sqrt(delta)) / (2 * a));
}

void draw_sp(t_v3 ray, t_sp *sp, t_img *img, t_v3 rayo)
{
	float	a;
	float	b;
	float	c;
	t_v3	oc;
	float	delta;

	oc.x = rayo.x - sp->pos.x;
	oc.y = rayo.y - sp->pos.y;
	oc.z = rayo.z - sp->pos.z;
	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b = 2.0f * (oc.x * ray.x + oc.y * ray.y + oc.z * ray.z);
	c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sp->dia/2 * sp->dia/2;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		if ((-b + sqrt(delta)) / (2.0f * a) || (-b - sqrt(delta)) / (2.0f * a))
			mlx_put_px(img, ray.px, ray.py, 0xFFFFFFFF);
	}
}

//
// void	draw_sp(t_v3 ray, t_sp *sp, t_img *img, t_v3 rayo)
// {
// 	float	a;
// 	float	b;
// 	float	c;
//
// 	// a = powf(ray.x, 2) + powf(ray.y, 2) + powf(ray.z, 2);
// 	// b = (2 * ray.x * powf(rayo.x - sp->pos.x, 2))
// 	// 	+ (2 * ray.y * powf(rayo.y - sp->pos.y, 2))
// 	// 	+ (2 * ray.z * powf(rayo.z - sp->pos.z, 2));
// 	// c = powf(rayo.x - sp->pos.x, 2)
// 	// 	+ powf(rayo.y - sp->pos.y, 2)
// 	// 	+ powf(rayo.z - sp->pos.z, 2);
// 	a = dot(ray, ray);
// 	b = 2 * dot(ray, vec_sub(rayo, sp->pos));
// 	c = dot(vec_sub(rayo, sp->pos), vec_sub(rayo, sp->pos)) - (sp->radius * sp->radius);
// 	if (second_degree(a, b, c, true) >= 0 || second_degree(a, b, c, false) >= 0)
// 		mlx_put_px(img, ray.px, ray.py, 0xFFFFFFFF);
// }

void	draw_sh(t_v3 ray, t_sc *sc, t_img *img, t_v3 pos)
{
	int	i;

	i = -1;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			draw_sp(ray, sc->elems[i].sh.sp, img, pos);
	}
	
}

static void	raytrace(t_sc *sc, t_img *img)
{
	t_ca	cam;
	int		j;
	float	co[2];
	t_v3	ray;
	int		i;
	FILE *file;

	cam = get_cam(sc);
	file = fopen("rays.log", "w");
	printf("cam.pos.x=%f\ncam.pos.y=%f\ncam.pos.z=%f\ncam.fw.x=%f\ncam.fw.y=%f\ncam.fw.z=%f\ncam.fov=%f\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.fw.x, cam.fw.y, cam.fw.z, cam.fov);
	printf("cam.up.x=%f\ncam.up.y=%f\ncam.up.z=%f\ncam.right.x=%f\ncam.right.y=%f\ncam.right.z=%f\ncam.scale=%f\ncam.asp=%f\n", cam.up.x, cam.up.y, cam.up.z, cam.right.x, cam.right.y, cam.right.z, cam.scale, cam.asp);
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			co[0] = (2 * ((i + 0.5)/WIDTH) - 1) * cam.asp * cam.scale;
			co[1] = (1 - 2 * ((j+ 0.5) / HEIGHT)) * cam.scale;
			ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]),
					vec_scale(cam.up, co[1])), cam.fw));
			ray.py = j;
			ray.px = i;
			draw_sh(ray, sc, img, cam.pos);
			fprintf(file, "|j:%3d| |i:%3d| |ray.x=%f| |ray.y=%f| |ray.z=%f|\n", j, i, ray.x, ray.y, ray.z);
		}
	}
	fclose(file);
}

int main(int ac, char **av)
{
	t_graph	graph;
	t_sc	*sc;

	(void)ac;

	if (graph_init(&graph) == -1)
		return (1);
	sc = init_scene(av[1]);
	// printf("cam.pos.x=%f\ncam.pos.y=%f\ncam.pos.z=%f\ncam.fw.x=%f\ncam.fw.y=%f\ncam.fw.z=%f\ncam.fov=%f\n", sc->elems[0].sh.ca->pos.x, sc->elems[0].sh.ca->pos.y, sc->elems[0].sh.ca->pos.z, sc->elems[0].sh.ca->fw.x, sc->elems[0].sh.ca->fw.y, sc->elems[0].sh.ca->fw.z, sc->elems[0].sh.ca->fov);
	//mlx_put_px(&graph.img, 50, 50, 0x00FF0000);
	
	raytrace(sc, &graph.img);
	ft_printf("DONE\n");
	mlx_put_image_to_window(graph.xsrv, graph.win, graph.img.self, 0, 0);
	draw_menu(&graph);
	
	mlx_hook(graph.win, KEYD, 1L << 0, keyhook, &graph);
	mlx_hook(graph.win, CLOSE_BTN, 0, close_win, &graph);
	mlx_loop(graph.xsrv);
	return (0);
}
