/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:40:24 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/11 10:40:24 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "math.h"

static int	ft_signer(char c, int *i)
{
	int	sign;

	sign = 1;
	if (c == '-')
	{
		sign *= -1;
		(*i)++;
	}
	else if (c == '+')
		(*i)++;
	return (sign);
}

static void	float_part(int *i, float *res, const char *str)
{
	float	fraction;
	int		decimal_places;

	(*i)++;
	fraction = 0.0f;
	decimal_places = 0;
	while (ft_isdigit(str[*i]))
	{
		fraction = fraction * 10.0f + (str[*i] - '0');
		decimal_places++;
		(*i)++;
	}
	*res += fraction / powf(10.0f, decimal_places);
}

float	ft_atof(const char *str)
{
	int		i;
	int		sign;
	float	res;

	if (!str)
		return (0.0f);
	res = 0.0f;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = ft_signer(str[i], &i);
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10.0f + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		float_part(&i, &res, str);
	return (res * sign);
}
