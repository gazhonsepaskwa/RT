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
		if (tmp[0])
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

t_sc	*init_scene(char *file)
{
	int		fd;
	t_sc	*sc;
	char	*str;
	char	**split;
	int		i;

	sc = malloc(sizeof(t_sc) * 1);
	if (!sc)
		return (NULL);
	sc->elems = malloc(sizeof(t_ele) * nb_objects(file));
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
			sc->elems[i].type = CAM;
			sc->elems[i].sh.ca = init_cam(split);
			i++;
		}
		else if (!ft_strncmp(split[0], "sp", -1))
		{
			sc->elems[i].type = SPHERE;
			sc->elems[i].sh.sp = init_sphere(split);
			i++;
		}
		free_tab(split);
		ft_free(&str);
		str = get_next_line(fd, 0);
	}
	close(fd);
	return (sc);
}
