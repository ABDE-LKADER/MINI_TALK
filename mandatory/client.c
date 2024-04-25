/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:34:21 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/25 10:10:06 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	error_handler(int ac, char *av)
{
	if (ac != 3)
	{
		ft_putstr_fd(RED"Usage: "RST, 2);
		ft_putendl_fd("./client <server_pid> <message>", 2);
		exit(EXIT_FAILURE);
	}
	while (*av)
	{
		if (!ft_strchr("-+0123456789", *av++))
		{
			ft_putendl_fd(RED"Error: "RST"Invalid server PID.", 2);
			ft_putstr_fd(YEL"-> Provide a valid PID ", 2);
			ft_putendl_fd("<numeric value only> ..."RST, 2);
			exit(EXIT_FAILURE);
		}
	}
}

static void	error_handler_plus(int server_pid)
{
	if (server_pid <= 0)
	{
		ft_putendl_fd(RED"Error: "RST"Invalid server PID."YEL, 2);
		ft_putendl_fd("-> Provide a valid PID <greater than 0> ..."RST, 2);
		exit(EXIT_FAILURE);
	}
	if (kill(server_pid, 0) == -1)
	{
		ft_putendl_fd(RED"Error: "RST"Invalid server PID."YEL, 2);
		ft_putendl_fd("-> Provide a valid PID <the server pid> ..."RST, 2);
		exit(EXIT_FAILURE);
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

int	main(int ac, char **av)
{
	pid_t	server_pid;

	signal(SIGUSR1, (void *)IGNORE);
	error_handler(ac, av[1]);
	server_pid = ft_atoi(av[1]);
	error_handler_plus(server_pid);
	while (*av[2])
		signal_handler(server_pid, *av[2]++);
	return (signal_handler(server_pid, '\n'), EXIT_SUCCESS);
}
