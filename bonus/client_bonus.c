/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:34:21 by abadouab          #+#    #+#             */
/*   Updated: 2024/01/07 21:46:39 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	error_handler(int ac, char *av)
{
	if (ac != 3)
	{
		write(2, "\033[1;31mUsage: ", 14);
		write(2, "\033[0m./client <server_pid> <message>\n", 36);
		exit (EXIT_FAILURE);
	}
	while (*av)
	{
		if (!ft_strchr("-+0123456789", *av++))
		{
			write(2, "\033[1;31mError: \033[0mInvalid server PID.\n", 38);
			write(2, "\033[0;33m-> Provide a valid PID ", 30);
			write(2, "<Numeric value only> please.\n", 29);
			exit (EXIT_FAILURE);
		}
	}
}

static void	signal_handler(int server_pid, unsigned char mes)
{
	int	num_bit;
	int	check_bits;

	num_bit = 8;
	check_bits = 128;
	while (num_bit--)
	{
		if (mes & check_bits)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		check_bits >>= 1;
		usleep(WAIT_TIME);
	}
}

void	feedback(int sig)
{
	(void)sig;
	ft_printf("\033[1;33m[SUCCESS]: \033[0m");
	ft_printf("Message was received to the server!\n");
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	signal(SIGUSR1, &feedback);
	error_handler(ac, av[1]);
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
	{
		write(2, "\033[1;31mError: \033[0mInvalid server PID.\n\033[0;33m", 45);
		write(2, "-> Provide a valid PID <greater than 0> please.\n", 48);
		return (EXIT_FAILURE);
	}
	while (*av[2])
		signal_handler(server_pid, *av[2]++);
	return (signal_handler(server_pid, '\0'),
		signal_handler(server_pid, '\n'), EXIT_SUCCESS);
}
