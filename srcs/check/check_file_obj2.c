/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_obj2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:11:42 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/25 09:11:42 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../includes/check.h"

int	check_cn(char **s, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(s) < 7 || tab_len(s) > 9)
		error += ac_error(l, line, "cn (x,y,z)[position] (x,y,z)[normal] \
(rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] \
(float)[exponent]", 9);
	error += format_vec(s[1], l, line, 1);
	error += format_vec(s[2], l, line, 2);
	error += format_rgb(s[3], l, line, 3);
	if (ft_atof(s[4]) > 1.0 || ft_atof(s[4]) < 0.0)
		error += raise_error(l, "Ambiant not in range [0.0-1.0]", line, 4);
	if (ft_atof(s[5]) > 1.0 || ft_atof(s[5]) < 0.0)
		error += raise_error(l, "Difuse not in range [0.0-1.0]", line, 5);
	if (ft_atof(s[6]) > 1.0 || ft_atof(s[6]) < 0.0)
		error += raise_error(l, "Specular not in range [0.0-1.0]", line, 6);
	return (error);
}

int	check_cl(char **s, char *line, int l)
{
	int		error;

	error = 0;
	if (tab_len(s) < 10 || tab_len(s) > 11)
		error += ac_error(l, line, "cl (x,y,z)[position] (x,y,z)[normal] \
(rgb)[color] (float)[ambiant] (float)[difuse] (float)[specular] \
(float)[exponent]", 10);
	error += format_vec(s[1], l, line, 1);
	error += format_vec(s[2], l, line, 2);
	if (!ft_isstrdigit(s[3]) || ft_atoi(s[3]) < 0)
		error += raise_error(l, "Cyl radius should be positive", line, 3);
	if (!ft_isstrdigit(s[4]) || ft_atoi(s[4]) < 0)
		error += raise_error(l, "Cyl height should be positive", line, 4);
	error += format_rgb(s[5], l, line, 5);
	if (!ft_isstrdigit(s[6]) || ft_atof(s[6]) > 1.0 || ft_atof(s[6]) < 0.0)
		error += raise_error(l, "Ambiant not in range [0.0-1.0]", line, 6);
	if (!ft_isstrdigit(s[7]) || ft_atof(s[7]) > 1.0 || ft_atof(s[7]) < 0.0)
		error += raise_error(l, "Difuse not in range [0.0-1.0]", line, 7);
	if (!ft_isstrdigit(s[8]) || ft_atof(s[8]) > 1.0 || ft_atof(s[8]) < 0.0)
		error += raise_error(l, "Specular not in range [0.0-1.0]", line, 8);
	return (error);
}
