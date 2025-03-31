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

#include "../../lib/libft/libft.h"
#include "../../includes/Scene.h"

#include <fcntl.h>

static	int	nb_objects(char *file, int i[2])
{
	int		fd;
	int		ret;
	char	*str;
	char	*tmp;

	ret = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd, 0);
	i[1] = 0;
	while (str)
	{
		tmp = ft_strtrim(str, " \n\t\v\r");
		if (tmp[0] && (ft_strncmp(str, "A", 1) && ft_strncmp(str, "C", 1) && ft_strncmp(str, "L", 1)))
			ret++;
		if (tmp[0] && !ft_strncmp(str, "L", 1))
			i[1] += 1;
		ft_free(&tmp);
		str = get_next_line(fd, 0);
	}
	str = get_next_line(fd, 0);
	ft_free(&str);
	close(fd);
	return (ret);
}

// static int	init_col(char *str)
// {
// 	char	**split;
// 	int		r;
// 	int		g;
// 	int		b;
//
// 	split = ft_split(str, ",");
// 	if (!split)
// 		return ((255 << 16) | (255 << 8) | 255);
// 	r = ft_atof(split[0]);
// 	g = ft_atof(split[1]);
// 	b = ft_atof(split[2]);
// 	free_tab(split);
// 	return ((r << 16) | (g << 8) | b);
// }

static t_co	init_acol(char *str)
{
	char	**split;
	t_co	co;

	split = ft_split(str, ",");
	if (!split)
		return ((t_co){0,0,0});
	co = init_color(split);
	return (co);
}

#include <stdio.h>
t_sc	*init_scene(char *file, void *xsrv)
{
	int		fd;
	t_sc	*sc;
	char	*str;
	char	**split;
	int		i[2];

	sc = malloc(sizeof(t_sc) * 1);
	if (!sc)
		return (NULL);
	sc->nb_objs = nb_objects(file, i);
	sc->nb_lig = i[1];
	sc->elems = malloc(sizeof(t_ele) * sc->nb_objs);
	// printf("i %d sc %d\n", i[1], sc->nb_objs);
	sc->lig = malloc(sizeof(t_li *) * sc->nb_lig);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free(sc), NULL);
	i[0] = 0;
	i[1] = 0;
	str = get_next_line(fd, 0);
	while (str)
	{
		split = ft_split(str, " \n\t\v");
		if (!split || !split[0])
		{
			ft_free(&str);
			str = get_next_line(fd, 0);
			continue ;
		}
		if (!ft_strncmp(split[0], "C", -1))
		{
			sc->cam = init_cam(split);
		}
		else if (!ft_strncmp(split[0], "sp", -1))
		{
			sc->elems[i[0]].type = SPHERE;
			sc->elems[i[0]].sh.sp = init_sphere(split, xsrv);
			i[0]++;
		}
		else if (!ft_strncmp(split[0], "A", -1))
		{
			sc->li = ft_atof(split[1]);
			sc->col = init_acol(split[2]);
		}
		else if (!ft_strncmp(split[0], "L", -1))
		{
			sc->lig[i[1]++] = init_light(split);
			// sc->elems[i[0]].type = LIGHT;
			// sc->elems[i[0]].sh.li = init_light(split);
			// i[0]++;
		}
		else if (!ft_strncmp(split[0], "pl", -1))
		{
			sc->elems[i[0]].type = PLANE;
			sc->elems[i[0]].sh.pl = init_plane(split, xsrv);
			i[0]++;
		}
		else if (!ft_strncmp(split[0], "cl", -1))
		{
			sc->elems[i[0]].type = CYLINDER;
			sc->elems[i[0]].sh.cl = init_cl(split);
			i[0]++;
		}
		else if (!ft_strncmp(split[0], "cn", -1))
		{
			sc->elems[i[0]].type = CONE;
			sc->elems[i[0]].sh.cn = init_cn(split);
			i[0]++;
		}
		free_tab(split);
		ft_free(&str);
		str = get_next_line(fd, 0);
	}
	close(fd);
	return (sc);
}
