/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:24:30 by abadouab          #+#    #+#             */
/*   Updated: 2024/01/01 17:59:08 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	print_char(char c)
{
	return (ft_putchar_fd(c, 1), 1);
}

int	print_string(char *str)
{
	if (!str)
		str = "(null)";
	return (ft_putstr_fd(str, 1), ft_strlen(str));
}

int	format_set(char format, va_list lstarg)
{
	int	print;

	print = 0;
	if (format == 'c')
		print += print_char(va_arg(lstarg, int));
	else if (format == 's')
		print += print_string(va_arg(lstarg, char *));
	else if (format == 'p')
		print += print_address(va_arg(lstarg, void *));
	else if (format == 'd' || format == 'i')
		print += print_num(va_arg(lstarg, int));
	else if (format == 'u')
		print += print_unum(va_arg(lstarg, unsigned int));
	else if (format == 'x' || format == 'X')
		print += print_hex(va_arg(lstarg, unsigned int), format);
	else if (format == '%')
		print += print_char(format);
	return (print);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		print;
	va_list	lstarg;

	i = 0;
	print = 0;
	va_start(lstarg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (ft_strchr("cspdiuxX%", format[i]))
				print += format_set(format[i], lstarg);
		}
		else
			print += print_char(format[i]);
		i++;
	}
	return (va_end(lstarg), print);
}
