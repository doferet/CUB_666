/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:50:19 by doferet           #+#    #+#             */
/*   Updated: 2023/11/20 12:28:34 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char *str, int len)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	temp = 0;
	end = len - 1;
	if (str[start] == '-')
		start++;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

static int	ft_count(long int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_boucle(int count, int i, int n, char *str)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		str[i] = '-';
		nb = -nb;
		i++;
	}
	while (i < count)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
		i++;
	}
	ft_swap(str, i);
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	int		i;
	long	nb;

	nb = n;
	count = ft_count(nb);
	i = 0;
	str = malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	if (str)
		str[0] = '0';
	return (ft_boucle(count, i, n, str));
}

/*#include <stdio.h>
int main(void)
{
	int n = -42;
	printf("%s\n", ft_itoa(n));
}*/
