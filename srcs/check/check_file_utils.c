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
	int	it;

	ft_fprintf(2, "Error\nscene_file:%d: %serror:%s %s\n", l, RED, RESET, error);
	ft_fprintf(2, "%s%s%s", GREY, line, RESET);
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
	ft_fprintf(2, "%s^%s\n", GREEN, RESET);
	return (1);
}

int	ac_error(int l, char *line, char *exp, int ac)
{
	ft_fprintf(2, "Error\nscene_file:%d: %serror:%s Object require %d args\n",
		l, RED, RESET, ac);
	ft_fprintf(2, "file:     %s%s%s", GREY, line, RESET);
	ft_fprintf(2, "expected: %s%s%s\n\n", GREY, exp, RESET);
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
