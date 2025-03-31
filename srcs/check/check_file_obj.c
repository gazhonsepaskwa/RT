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

#include <stdbool.h>

int	check_ca(char **s, char *line, int l)
{
	int			error;
	static bool	used = false;

	error = 0;
	if (used)
		error += raise_error(l, "Only one camera allowed", line, 0);
	used = true;
	if (tab_len(s) != 4)
		error += ac_error(l, line, "C (vec)[pos] (vec)[forward] (int_4)[fov]",
				4);
	error += format_vec(s[1], l, line, 1);
	error += format_vec(s[2], l, line, 2);
	if (!ft_isstrdigit(s[3]) || ft_atoi(s[3]) > 180 || ft_atoi(s[3]) < 0)
		error += raise_error(l, "fov should be in range [0-180]", line, 3);
	return (error);
}

int	check_am(char **s, char *line, int l)
{
	int		error;
	static bool	used = false;

	error = 0;
	if (used)
		error += raise_error(l, "Only one ambiant allowed", line, 0);
	used = true;
	if (tab_len(s) != 3)
		error += ac_error(l, line, "A (float)[intensity] (rgb)[color]",
				3);
	if (!ft_isstrdigit(s[1]) || ft_atof(s[1]) > 1.0 || ft_atof(s[1]) < 0.0)
		error += raise_error(l, "Ambiant light intensity \
should be in range [0.0-1.0]", line, 1);
	error += format_rgb(s[2], l, line, 2);
	return (error);
}

int	check_li(char **s, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(s) != 4)
		error += ac_error(l, line, "L (x,y,z)[position] (float)[intensity] \
(rgb)[color]", 4);
	error += format_vec(s[1], l, line, 1);
	if (!ft_isstrdigit(s[2]) || ft_atof(s[2]) > 1.0 || ft_atof(s[2]) < 0.0)
		error += raise_error(l, "Intensity not in range [0.0-1.0]", line, 2);
	error += format_rgb(s[3], l, line, 3);
	return (error);
}

int	check_sp(char **s, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(s) < 8 || tab_len(s) > 9)
		error += ac_error(l, line, "sp (x,y,z)[position] (int)[radius] \
(rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] \
(float)[exponent]", 9);
	error += format_vec(s[1], l, line, 1);
	if (!ft_isstrdigit(s[2]) || ft_atoi(s[2]) < 0)
		error += raise_error(l, "Sphere radius should be positive", line, 2);
	error += format_rgb(s[3], l, line, 3);
	if (!ft_isstrdigit(s[4]) || ft_atof(s[4]) > 1.0 || ft_atof(s[4]) < 0.0)
		error += raise_error(l, "Ambiant not in range [0.0-1.0]", line, 4);
	if (!ft_isstrdigit(s[5]) || ft_atof(s[5]) > 1.0 || ft_atof(s[5]) < 0.0)
		error += raise_error(l, "Difuse not in range [0.0-1.0]", line, 5);
	if (!ft_isstrdigit(s[6]) || ft_atof(s[6]) > 1.0 || ft_atof(s[6]) < 0.0)
		error += raise_error(l, "Specular not in range [0.0-1.0]", line, 6);
	return (error);
}

int	check_pl(char **s, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(s) < 7 || tab_len(s) > 9)
		error += ac_error(l, line, "pl (x,y,z)[position] (x,y,z)[normal] \
(rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] \
(float)[exponent]", 9);
	error += format_vec(s[1], l, line, 1);
	error += format_vec(s[2], l, line, 2);
	error += format_rgb(s[3], l, line, 3);
	if (!ft_isstrdigit(s[4]) || ft_atof(s[4]) > 1.0 || ft_atof(s[4]) < 0.0)
		error += raise_error(l, "Ambiant not in range [0.0-1.0]", line, 4);
	if (!ft_isstrdigit(s[5]) || ft_atof(s[5]) > 1.0 || ft_atof(s[5]) < 0.0)
		error += raise_error(l, "Difuse not in range [0.0-1.0]", line, 5);
	if (!ft_isstrdigit(s[6]) || ft_atof(s[6]) > 1.0 || ft_atof(s[6]) < 0.0)
		error += raise_error(l, "Specular not in range [0.0-1.0]", line, 6);
	return (error);
}
