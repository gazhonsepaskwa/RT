/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:40:01 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 10:40:01 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Scene.h"
#include "../../lib/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static	int	nb_objects(char *file)
{
	int		fd;
	int		ret;
	char	*str;
	char	*tmp;

	ret = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd, 0);
	while (str)
	{
		tmp = ft_strtrim(str, " \n\t\v\r");
		if (tmp[0] && (ft_strncmp(str, "A", 1) && ft_strncmp(str, "C", 1)))
			ret++;
		ft_free(&tmp);
		str = get_next_line(fd, 0);
	}
	str = get_next_line(fd, 0);
	ft_free(&str);
	close(fd);
	printf("ret: %d\n", ret);
	return (ret);
}

static int	init_color(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ",");
	if (!split)
		return ((255 << 16) | (255 << 8) | 255);
	r = ft_atof(split[0]);
	g = ft_atof(split[1]);
	b = ft_atof(split[2]);
	free_tab(split);
	return ((r << 16) | (g << 8) | b);
}

static t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	return (pos);
}

t_li *getLight(t_sc *sc)
{
	int		i;

	i = -1;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == LIGHT)
			return (sc->elems[i].sh.li);
	}
	return (NULL);
}

static t_li	*init_light(char **split)
{
	t_li	*li;
	char	**arg;

	li = malloc(sizeof(t_li) * 1);
	if (!li)
		return (NULL);
	arg = ft_split(split[1], ",");
	if (!arg)
		return (free(li), NULL);
	li->pos = init_pos(arg);
	free_tab(arg);
	li->li = ft_atof(split[2]);
	return (li);
}

t_sc	*init_scene(char *file, void *xsrv)
{
	int		fd;
	t_sc	*sc;
	char	*str;
	char	**split;
	int		i;

	sc = malloc(sizeof(t_sc) * 1);
	if (!sc)
		return (NULL);
	sc->nb_objs = nb_objects(file);
	sc->elems = malloc(sizeof(t_ele) * sc->nb_objs);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free(sc), NULL);
	i = 0;
	str = get_next_line(fd, 0);
	while (str)
	{
		split = ft_split(str, " ");
		if (!ft_strncmp(split[0], "C", -1))
		{
			sc->cam = init_cam(split);
		}
		else if (!ft_strncmp(split[0], "sp", -1))
		{
			sc->elems[i].type = SPHERE;
			sc->elems[i].sh.sp = init_sphere(split, xsrv);
			i++;
		}
		else if (!ft_strncmp(split[0], "A", -1))
		{
			sc->li = ft_atof(split[1]);
			sc->color = init_color(split[2]);
		}
		else if (!ft_strncmp(split[0], "L", -1))
		{
			sc->elems[i].type = LIGHT;
			sc->elems[i].sh.li = init_light(split);
			i++;
		}
		else if (!ft_strncmp(split[0], "pl", -1))
		{
			sc->elems[i].type = PLANE;
			sc->elems[i].sh.pl = init_plane(split);
			i++;
		}
		else if (!ft_strncmp(split[0], "cl", -1))
		{
			sc->elems[i].type = CYLINDER;
			sc->elems[i].sh.cl = init_cl(split);
			i++;
		}
		free_tab(split);
		ft_free(&str);
		str = get_next_line(fd, 0);
	}
	close(fd);
	return (sc);
}
