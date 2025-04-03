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
		if (tmp[0] && (ft_strncmp(str, "A", 1) && ft_strncmp(str, "C", 1)
				&& ft_strncmp(str, "L", 1)))
			ret++;
		if (tmp[0] && !ft_strncmp(str, "L", 1))
			i[1] += 1;
		ft_free(&tmp);
		ft_free(&str);
		str = get_next_line(fd, 0);
	}
	str = get_next_line(fd, 0);
	ft_free(&str);
	close(fd);
	return (ret);
}

static t_sc	*init_var(char *file)
{
	t_sc	*sc;
	int		i[2];

	sc = malloc(sizeof(t_sc) * 1);
	if (!sc)
		return (NULL);
	sc->nb_objs = nb_objects(file, i);
	sc->nb_lig = i[1];
	sc->elems = malloc(sizeof(t_ele) * sc->nb_objs);
	if (!sc->elems)
		return (NULL);
	sc->lig = malloc(sizeof(t_li *) * sc->nb_lig);
	if (!sc->lig)
		return (NULL);
	return (sc);
}

t_sc	*init_scene(char *file, void *xsrv)
{
	int		fd;
	t_sc	*sc;

	sc = init_var(file);
	if (!sc)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free_lights(sc), free(sc->elems), free(sc), NULL);
	init_objs(fd, sc, xsrv);
	if (access("./assets/HDRI/hdri.xpm", F_OK | R_OK) == 0)
		load_texture(&sc->hdri.tex.b, "./assets/HDRI/hdri.xpm", xsrv);
	sc->hdri.fw = (t_v3){1, 0, 0, 0, 0};
	sc->hdri.ri = (t_v3){0, 0, 1, 0, 0};
	sc->hdri.up = (t_v3){0, 1, 0, 0, 0};
	sc->hdri.pos = (t_v3){0, 0, 0, 0, 0};
	close(fd);
	return (sc);
}
