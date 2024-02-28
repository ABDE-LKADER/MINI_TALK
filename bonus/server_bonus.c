/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:34:17 by abadouab          #+#    #+#             */
/*   Updated: 2024/01/09 18:22:09 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_set_bit = 128;

void	check_pid(int *old_pid, int new_pid, int *mess, int *bits)
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
		if (!mess)
			kill(sig_inf->si_pid, SIGUSR1);
		ft_printf("%c", mess);
		bits = 0;
		mess = 0;
		g_set_bit = 128;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	ft_printf("The server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
