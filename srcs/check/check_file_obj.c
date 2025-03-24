/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:10:20 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/22 16:10:20 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../includes/check.h"

int	check_ca(char **split, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(split) != 4)
		error += ac_error(l, line, "C (vec)[pos] (vec)[forward] (int_4)[fov]",
				(int[2]){4, tab_len(split)});
	error += format_vec(split[1], l, line, 1);
	error += format_vec(split[2], l, line, 2);
	if (ft_atoi(split[3]) > 180 || ft_atoi(split[3]) < 0)
		error += raise_error(l, "fov should be in range [0-180]", line, 3);
	return (error);
}

int	check_am(char **split, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(split) != 3)
		error += ac_error(l, line, "A (float)[intensity] (rgb)[color]",
				(int[2]){3, tab_len(split)});
	if (ft_atof(split[1]) > 1.0 || ft_atof(split[1]) < 0.0)
		error += raise_error(l, "Ambiant light intensity \
should be in range [0.0-1.0]", line, 1);
	error += format_rgb(split[2], l, line, 2);
	return (error);
}

int	check_li(char **split, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(split) != 4)
		error += ac_error(l, line, "L (x,y,z)[position] (float)[intensity] \
(rgb)[color]", (int[2]){4, tab_len(split)});
	error += format_vec(split[1], l, line, 1);
	if (ft_atof(split[2]) > 1.0 || ft_atof(split[2]) < 0.0)
		error += raise_error(l, "Light intensity should be in range \
[0.0-1.0]", line, 2);
	error += format_rgb(split[3], l, line, 3);
	return (error);
}

int	check_sp(char **split, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(split) < 8 || tab_len(split) > 9)
		error += ac_error(l, line, "sp (x,y,z)[position] (int)[radius] \
(rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] \
(float)[exponent]", (int[2]){9, tab_len(split)});
	error += format_vec(split[1], l, line, 1);
	if (ft_atoi(split[2]) < 0)
		error += raise_error(l, "Sphere radius should be positive", line, 2);
	error += format_rgb(split[3], l, line, 3);
	if (ft_atof(split[4]) > 1.0 || ft_atof(split[4]) < 0.0)
		error += raise_error(l, "Ambiant composant should be in range \
[0.0-1.0]", line, 4);
	if (ft_atof(split[5]) > 1.0 || ft_atof(split[4]) < 0.0)
		error += raise_error(l, "Difuse composant should be in range \
[0.0-1.0]", line, 5);
	if (ft_atof(split[6]) > 1.0 || ft_atof(split[4]) < 0.0)
		error += raise_error(l, "Specular composant should be in range \
[0.0-1.0]", line, 6);
	return (error);
}

int	check_pl(char **split, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(split) < 8 || tab_len(split) > 9)
		error += ac_error(l, line, "pl (x,y,z)[position] (x,y,z)[normal] \
(rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] \
(float)[exponent]", (int[2]){9, tab_len(split)});
	error += format_vec(split[1], l, line, 1);
	error += format_vec(split[2], l, line, 2);
	error += format_rgb(split[3], l, line, 3);
	if (ft_atof(split[4]) > 1.0 || ft_atof(split[4]) < 0.0)
		error += raise_error(l, "Ambiant composant should be in range \
[0.0-1.0]", line, 4);
	if (ft_atof(split[5]) > 1.0 || ft_atof(split[4]) < 0.0)
		error += raise_error(l, "Difuse composant should be in range \
[0.0-1.0]", line, 5);
	if (ft_atof(split[6]) > 1.0 || ft_atof(split[4]) < 0.0)
		error += raise_error(l, "Specular composant should be in range \
[0.0-1.0]", line, 6);
	return (error);
}
