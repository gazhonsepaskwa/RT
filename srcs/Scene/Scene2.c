/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:35:03 by nalebrun          #+#    #+#             */
/*   Updated: 2025/04/01 12:35:03 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../includes/Scene.h"

static t_co	init_acol(char *str)
{
	char	**split;
	t_co	co;

	split = ft_split(str, ",");
	if (!split)
		return ((t_co){0, 0, 0});
	co = init_color(split);
	free_tab(split);
	return (co);
}

static void	init_objp1(char **split, t_sc *sc, int i[2], void *xsrv)
{
	if (!ft_strncmp(split[0], "C", -1))
		sc->cam = init_cam(split);
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
		sc->lig[i[1]++] = init_light(split);
}

static void	init_objp2(char **split, t_sc *sc, int i[2], void *xsrv)
{
	if (!ft_strncmp(split[0], "pl", -1))
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
}

void	init_objs(int fd, t_sc *sc, void *xsrv)
{
	char	**split;
	char	*str;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	str = get_next_line(fd, 0);
	while (str)
	{
		split = ft_split(str, " \n\t\v");
		if (!split || !split[0])
		{
			free_tab(split);
			ft_free(&str);
			str = get_next_line(fd, 0);
			continue ;
		}
		init_objp1(split, sc, i, xsrv);
		init_objp2(split, sc, i, xsrv);
		free_tab(split);
		ft_free(&str);
		str = get_next_line(fd, 0);
	}
}
