/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:34:17 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/19 11:44:52 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_set_bit = 128;

static void	error_handler(void)
{
	write(2, RED"Usage: "RST, 18);
	write(2, "./server <empty>\n", 17);
	exit (EXIT_FAILURE);
}

static void	check_pid(int new_pid, t_data *data)
{
	if (data->old_pid != new_pid)
	{
		data->bits = 0;
		data->set = 0;
		data->bytes = 0;
		data->mess = 0;
		g_set_bit = 128;
	}
	data->old_pid = new_pid;
}

static void	message_handler(t_data *data)
{
	if (!data->check)
	{
		if (data->mess >= 240)
			data->bytes = 4;
		else if (data->mess >= 224)
			data->bytes = 3;
		else if (data->mess >= 192)
			data->bytes = 2;
		data->check = 1;
	}
	if (data->set < data->bytes)
		data->save[data->set++] = data->mess;
	if (!data->bytes)
	{
		ft_printf("%c", data->mess);
		data->check = 0;
	}
	else if (data->bytes == data->set)
	{
		ft_printf("%s", data->save);
		ft_bzero(data->save, SIZE);
		(1) && (data->bytes = 0, data->check = 0, data->set = 0);
	}
	(1) && (data->bits = 0, data->mess = 0, g_set_bit = 128);
}

static void	signal_handler(int signal_client, siginfo_t *sig_inf, void *none)
{
	static t_data	data;

	(void)none;
	check_pid(sig_inf->si_pid, &data);
	if (signal_client == SIGUSR1)
		data.mess |= g_set_bit;
	g_set_bit >>= 1;
	data.bits++;
	if (data.bits == 8 && data.mess)
		message_handler(&data);
	if (data.bits == 8 && !data.mess)
		kill(sig_inf->si_pid, SIGUSR1);
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
