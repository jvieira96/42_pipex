/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:05:52 by jpedro-f          #+#    #+#             */
/*   Updated: 2024/10/21 15:08:36 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// returns the string len

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int main(void)
// {
// 	char	*str = "olaola";

// 	printf("%d", ft_strlen(str));
// 	return(0);
// }