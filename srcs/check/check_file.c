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
#include "../../includes/check.h"
#include <unistd.h>

int	check_obj(int lc, char *line)
{
	char	**split;
	int		error;

	error = 0;
	split = ft_split(line, " \t\n\v");
	if (!ft_strncmp(split[0], "C", -1))
		error += check_ca(split, line, lc);
	else if (!ft_strncmp(split[0], "A", -1))
		error += check_am(split, line, lc);
	else if (!ft_strncmp(split[0], "L", -1))
		error += check_li(split, line, lc);
	else if (!ft_strncmp(split[0], "sp", -1))
		error += check_sp(split, line, lc);
	else if (!ft_strncmp(split[0], "pl", -1))
		error += check_pl(split, line, lc);
	else if (!ft_strncmp(split[0], "cl", -1))
		error += check_cl(split, line, lc);
	else if (!ft_strncmp(split[0], "cn", -1))
		error += check_cn(split, line, lc);
	else
		error += raise_error(lc, "unreconized Object type", line, 0);
	free_tab(split);
	return (error);
}

static void	summary(int fd, int error)
{
	get_next_line(fd, 1);
	if (error)
		ft_fprintf(2, "%sFile error sumarry%s : %d error raised\n",
			BOLD_WHITE, RESET, error);
	close(fd);
}

int	check_file(char *file)
{
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
			ft_free(&line);
			line = get_next_line(fd, 0);
			lc++;
			continue ;
		}
		error += check_obj(lc, line);
		ft_free(&line);
		line = get_next_line(fd, 0);
		lc++;
	}
	summary(fd, error);
	return (error);
}
