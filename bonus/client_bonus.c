/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:34:21 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:36 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	error_handler(int ac, char *av)
{
	if (ac != 3)
	{
		write(2, RED"Usage: "RST, 18);
		write(2, "./client <server_pid> <message>\n", 32);
		exit (EXIT_FAILURE);
	}
	while (*av)
	{
		if (!ft_strchr("-+0123456789", *av++))
		{
			write(2, RED"Error: "RST"Invalid server PID.\n", 38);
			write(2, YEL"-> Provide a valid PID ", 30);
			write(2, "<numeric value only> please.\n", 29);
			exit (EXIT_FAILURE);
		}
	}
}

static void	error_handler_plus(int server_pid)
{
	if (kill(server_pid, 0) == -1)
	{
		write(2, RED"Error: "RST"Invalid server PID.\n"YEL, 45);
		write(2, "-> Provide a valid PID <the server pid> please.\n", 48);
		exit (EXIT_FAILURE);
	}
	if (server_pid <= 0)
	{
		write(2, RED"Error: "RST"Invalid server PID.\n"YEL, 45);
		write(2, "-> Provide a valid PID <greater than 0> please.\n", 48);
		exit (EXIT_FAILURE);
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

static void	feedback(int sig)
{
	(void)sig;
	ft_printf("\033[1;33m[SUCCESS]: \033[0m");
	ft_printf("Message was received to the server!\n");
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	signal(SIGUSR1, feedback);
	error_handler(ac, av[1]);
	server_pid = ft_atoi(av[1]);
	error_handler_plus(server_pid);
	while (*av[2])
		signal_handler(server_pid, *av[2]++);
	return (signal_handler(server_pid, '\0'),
		signal_handler(server_pid, '\n'), EXIT_SUCCESS);
}
