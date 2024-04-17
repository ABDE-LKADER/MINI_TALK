/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:34:17 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/17 17:26:12 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_set_bit = 128;

static void	error_handler(void)
{
	write(2, RED"Usage: "RST, 18);
	write(2, "./server <empty>\n", 17);
	exit (EXIT_FAILURE);
}

static void	check_pid(int *old_pid, int new_pid, int *mess, int *bits)
{
	if (*old_pid != new_pid)
	{
		*bits = 0;
		*mess = 0;
		g_set_bit = 128;
	}
	*old_pid = new_pid;
}

static void	signal_handler(int signal_client, siginfo_t *sig_inf, void *none)
{
	static int	old_pid = 0;
	static int	bits = 0;
	static int	mess = 0;

	(void)none;
	check_pid(&old_pid, sig_inf->si_pid, &mess, &bits);
	if (signal_client == SIGUSR1)
		mess |= g_set_bit;
	g_set_bit >>= 1;
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", mess);
		bits = 0;
		mess = 0;
		g_set_bit = 128;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
		error_handler();
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("The server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
