/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:13:13 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/19 10:57:01 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "mylib.h"
# include <signal.h>

# define GRN "\033[1;32m"
# define YEL "\033[0;33m"
# define YLW "\033[0;33m"
# define RED "\033[1;31m"
# define RST "\033[0m"

# define BYTE 8
# define WAIT_TIME 400

typedef struct s_data
{
	int				set;
	int				mess;
	int				bits;
	int				bytes;
	int				check;
	int				old_pid;
	unsigned char	save[BYTE];
}					t_data;

#endif
