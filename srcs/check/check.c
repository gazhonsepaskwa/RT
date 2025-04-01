/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:01:56 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/21 10:01:56 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../includes/check.h"

#include <stdbool.h>
#include <fcntl.h>

int	check_extention(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len >= 4 && file[len - 1] == 't' && file[len - 2] == 'r'
		&& file[len - 3] == '.')
		return (1);
	return (0);
}

int	check_perm(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_error("Error\nCannot open file: can't read or does not exist\n");
		close(fd);
		return (0);
	}
	close(fd);
	fd = open(file, O_WRONLY);
	if (fd < 0)
	{
		ft_error("Error\nCannot open file: Is a folder\n");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	check(int ac, char **av)
{
	if (ac != 2 || !check_extention(av[1]))
	{
		ft_error("Error\nUsage : ./minirt x.rt\n");
		return (0);
	}
	if (!check_perm(av[1]) || check_file(av[1]))
		return (0);
	return (1);
}
