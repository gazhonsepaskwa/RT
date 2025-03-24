/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:31:07 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/21 11:31:07 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	count_strings(char *s, char *set)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (!is_charset(s[i], set) && (!s[i + 1] || is_charset(s[i + 1], set)))
			ret++;
		i++;
	}
	return (ret);
}

static	void	build_str(char const *src, char *dest, char *set)
{
	int	i;

	i = 0;
	while (src[i] && !is_charset(src[i], set))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static	char	**build_tab(char **tab, char const *s, char *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (tab && s[i])
	{
		if (is_charset(s[i], set))
			i++;
		else
		{
			j = 0;
			while (!is_charset(s[i + j], set) && s[i + j])
				j++;
			tab[count] = ft_calloc((j + 1), sizeof(char));
			if (!tab[count])
				return (free_all(tab, count));
			build_str(&s[i], tab[count++], set);
			i = i + j;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char *set)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = count_strings((char *)s, set);
	tab = ft_calloc(count + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[count] = 0;
	tab = build_tab(tab, s, set);
	return (tab);
}
