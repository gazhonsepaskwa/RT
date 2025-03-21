/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:36:02 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/21 11:36:02 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include <unistd.h>

int	raise_error(int l, char *error, char *line, int elem)
{
	int	spaces;
	int it;

	ft_printf("scene_file:%d: %serror:%s %s\n", l, RED, RESET, error);
	ft_printf("%s%s%s", GREY, line, RESET);
	spaces = 0;
	it = 0;
	while (it < elem)
	{
		spaces++;
		if (ft_strchr(" \t\n\v", line[spaces]))
		{
			it++;
			while (ft_strchr(" \t\n\v", line[spaces]))
				spaces++;
		}
	}
	while (spaces--)
		write(1, " ", 1);
	ft_printf("%s^%s\n", GREEN, RESET);

	return (1);
}

int	ac_error(int l, char *line, char *exp, int ac[2])
{
	ft_printf("scene_file:%d: %serror:%s Object require %d arg but have %d\n", l, RED, RESET, ac[0], ac[1]);
	ft_printf("file:     %s%s%s", GREY, line, RESET);
	ft_printf("expected: %s%s%s\n\n", GREY, exp, RESET);
	return (1);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int check_ca(char **split, char *line, int l)
{
	char	**sub;
	int		error;

	error = 0;
	if (tab_len(split) != 4)
		error += ac_error(l, line, "C (vec)[pos] (vec)[forward] (int_4)[fov]", (int[2]){4, tab_len(split)});
	sub = ft_split(split[1], ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "Format of position arg incorect: should be x,y,z", line, 1);
	free(sub);
	sub = ft_split(split[2], ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "Format of forward vec arg incorect: should be x,y,z", line, 2);
	free(sub);
	if (ft_atoi(split[3]) > 180 || ft_atoi(split[3]) < 0)
		error += raise_error(l, "fov should be in range [0-180]", line, 3);
	return (error);
}

int check_am(char **split, char *line, int l)
{
	char	**sub;
	int		error;

	error = 0;
	if (tab_len(split) != 3)
		error += ac_error(l, line, "A (float)[intensity] (rgb)[color]", (int[2]){3, tab_len(split)});
	if (ft_atof(split[1]) > 1.0 || ft_atof(split[1]) < 0.0)
		error += raise_error(l, "Ambiant light intensity should be in range [0.0-1.0]", line, 1);
	sub = ft_split(split[2], ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "format of color arg incorect: should be r,g,b", line, 2);
	if (ft_atoi(sub[0]) > 255 || ft_atoi(sub[0]) < 0
		|| ft_atoi(sub[1]) > 255 || ft_atoi(sub[1]) < 0
		|| ft_atoi(sub[2]) > 255 || ft_atoi(sub[2]) < 0)
		error += raise_error(l, "format of color arg incorect: should be in range [0-255]", line, 2);
	free(sub);
	return (error);
}

int check_li(char **split, char *line, int l)
{
	char	**sub;
	int		error;

	error = 0;
	if (tab_len(split) != 4)
		error += ac_error(l, line, "L (x,y,z)[position] (float)[intensity] (rgb)[color]", (int[2]){4, tab_len(split)});
	sub = ft_split(split[1], ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "Format of position arg incorect: should be x,y,z", line, 1);
	free(sub);
	if (ft_atof(split[2]) > 1.0 || ft_atof(split[2]) < 0.0)
		error += raise_error(l, "Light intensity should be in range [0.0-1.0]", line, 2);
	sub = ft_split(split[3], ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "format of color arg incorect: should be r,g,b", line, 3);
	if (ft_atoi(sub[0]) > 255 || ft_atoi(sub[0]) < 0
		|| ft_atoi(sub[1]) > 255 || ft_atoi(sub[1]) < 0
		|| ft_atoi(sub[2]) > 255 || ft_atoi(sub[2]) < 0)
		error += raise_error(l, "format of color arg incorect: should be in range [0-255]", line, 3);
	free(sub);
	return (error);
}

int check_sp(char **split, char *line, int l)
{
	// char	**sub;
	int		error;

	error = 0;
	if (tab_len(split) < 8 || tab_len(split) > 9)
		error += ac_error(l, line, "sp (x,y,z)[position] (int)[radius] (rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] (float)[exponent]", (int[2]){4, tab_len(split)});
	// sub = ft_split(split[1], ",");
	// if (tab_len(sub) != 3)
	// 	error += raise_error(l, "Format of position arg incorect: should be x,y,z", line, 1);
	// free(sub);
	// if (ft_atof(split[2]) > 1.0 || ft_atof(split[2]) < 0.0)
	// 	error += raise_error(l, "Light intensity should be in range [0.0-1.0]", line, 2);
	// sub = ft_split(split[3], ",");
	// if (tab_len(sub) != 3)
	// 	error += raise_error(l, "format of color arg incorect: should be r,g,b", line, 3);
	// if (ft_atoi(sub[0]) > 255 || ft_atoi(sub[0]) < 0
	// 	|| ft_atoi(sub[1]) > 255 || ft_atoi(sub[1]) < 0
	// 	|| ft_atoi(sub[2]) > 255 || ft_atoi(sub[2]) < 0)
	// 	error += raise_error(l, "format of color arg incorect: should be in range [0-255]", line, 3);
	// free(sub);
	return (error);
}

int	check_file(char *file)
{
	char	**split;
	char	*line;
	int		error;
	int		fd;
	int		lc;

	fd = open(file, O_RDONLY);
	lc = 1;
	line = get_next_line(fd, 0);
	error = 0;
	while (line)
	{
		if (!ft_strncmp(line, "", -1) || is_only_space(line))
		{
			line = get_next_line(fd, 0);
			continue ;
		}
		split = ft_split(line, " \t\n\v");
		if (!ft_strncmp(split[0],"C", -1))
			error += check_ca(split, line, lc);
		else if (!ft_strncmp(split[0],"A", -1))
			error += check_am(split, line, lc);
		else if (!ft_strncmp(split[0],"L", -1))
			error += check_li(split, line, lc);
		else if (!ft_strncmp(split[0],"sp", -1))
			error += check_sp(split, line, lc);
		// else if (!ft_strncmp(split[0],"pl", -1))
			// check_pl(split);
		// else if (!ft_strncmp(split[0],"cy", -1))
			// check_cyl(split);
		// else
			// error += raise_error(lc, "unreconized Object type", line, 0);

		line = get_next_line(fd, 0);
		free(split);
		lc++;
	}
	if (error)
		ft_printf("%sFile error sumarry%s : %d error raised\n", BOLD_WHITE, RESET, error);
	return (error);
}
