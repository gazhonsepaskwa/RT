/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:34:12 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 09:34:12 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "../includes/Cam.h"
#include "../includes/Sphere.h"
#include <fcntl.h>
#include <stdio.h>

static void	return_error(char *msg, int ret)
{
	ft_fprintf(2, "%s", msg);
	exit(ret);
}

int	main(int ac, char **av)
{
	int		fd;
	t_ca	*cam;
	t_sp	*sphere;
	char	*str;
	char	**split;

	if (ac != 2)
		return_error("Error: Expected ./miniRT file.rt\n", 1);
	cam = NULL;
	sphere = NULL;
	fd = open(av[1], O_RDONLY);
	str = get_next_line(fd, 0);
	while (str)
	{
		split = ft_split (str, " ");
		if (!ft_strncmp(split[0], "C", -1))
			cam = init_cam(split);
		else if (!ft_strncmp(split[0], "sp", -1))
			sphere = init_sphere(split);
		free_tab(split);
		ft_free(&str);
		str = get_next_line(fd, 0);
	}
	printf("cam.pos.x=%f\ncam.pos.y=%f\ncam.pos.z=%f\ncam.fw.x=%f\ncam.fw.y=%f\ncam.fw.z=%f\ncam.fov=%f\n", cam->pos.x, cam->pos.y, cam->pos.z, cam->fw.x, cam->fw.y, cam->fw.z, cam->fov);
	printf("sphere.pos.x=%f\nsphere.pos.y=%f\nsphere.pos.z=%f\nsphere.dia=%f\n", sphere->pos.x, sphere->pos.y, sphere->pos.z, sphere->dia);
}
