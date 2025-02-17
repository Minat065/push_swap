/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:31:53 by mirokugo          #+#    #+#             */
/*   Updated: 2024/05/03 17:41:54 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putmin(int nb, int fd)
{
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb == 0)
		write(fd, "0", 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int		i;
	char	nmb[10];

	putmin(nb, fd);
	if (nb == -2147483648 || nb == 0)
		return ;
	else if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar_fd('-', fd);
	}
	i = 0;
	while (nb != 0)
	{
		nmb[i] = (nb % 10) + 48;
		nb = nb / 10;
		i++;
	}
	i--;
	while (i >= 0)
		ft_putchar_fd(nmb[i--], fd);
}

/* int	main(void)
{
	ft_putnbr_fd(42, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(0, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-42, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-2147483648, 1);
	ft_putchar_fd('\n', 1);
	return (0);
} */
