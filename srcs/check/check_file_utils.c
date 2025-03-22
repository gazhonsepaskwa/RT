/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:15:37 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/22 16:15:37 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"

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
