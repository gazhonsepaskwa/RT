/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_obj_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:32:21 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/22 16:32:21 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/check.h"
#include "../../lib/libft/libft.h"

int	format_rgb(char *split, int l, char *line, int arg)
{
	char	**sub;
	int		error;

	error = 0;
	sub = ft_split(split, ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "Format of color arg incorect: \
should be r,g,b", line, arg);
	if (!ft_isstrdigit(sub[0]) || ft_atoi(sub[0]) > 255 || ft_atoi(sub[0]) < 0
		|| !ft_isstrdigit(sub[1]) || ft_atoi(sub[1]) > 255
		|| ft_atoi(sub[1]) < 0 || !ft_isstrdigit(sub[2])
		|| ft_atoi(sub[2]) > 255 || ft_atoi(sub[2]) < 0)
		error += raise_error(l, "Format of color arg incorect: \
should be in range [0-255]", line, arg);
	free_tab(sub);
	return (error);
}

int	format_vec(char *split, int l, char *line, int arg)
{
	char	**sub;
	int		error;

	error = 0;
	sub = ft_split(split, ",");
	if (tab_len(sub) != 3)
		error += raise_error(l, "Format of vector arg incorect: \
should be vx,vy,vz", line, arg);
	if (!ft_isstrdigit(sub[0]) || !ft_isstrdigit(sub[1])
		|| !ft_isstrdigit(sub[2]))
		error += raise_error(l, "Format of vector arg incorect: \
should be a float", line, arg);
	free_tab(sub);
	return (error);
}
