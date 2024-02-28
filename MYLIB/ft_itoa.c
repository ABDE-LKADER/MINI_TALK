/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:08:21 by abadouab          #+#    #+#             */
/*   Updated: 2023/12/28 09:13:40 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static int	get_len(int n)
{
	int	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	num;
	char			*snum;

	len = get_len(n);
	snum = malloc((len + 1) * sizeof(char));
	if (!snum)
		return (NULL);
	if (n < 0)
		num = -n;
	else
		num = n;
	snum[len] = '\0';
	while (len--)
	{
		snum[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		snum[0] = '-';
	return (snum);
}
