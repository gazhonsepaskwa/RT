/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:02:18 by nalebrun          #+#    #+#             */
/*   Updated: 2024/11/25 16:14:43 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_isstrdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!((s[i] >= 48 && s[i] <= 57) || s[i] == '.'))
			return (0);
		i++;
	}
	return (1);
}
