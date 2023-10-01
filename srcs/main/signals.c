/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:21:28 by codespace         #+#    #+#             */
/*   Updated: 2023/08/16 23:03:00 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	struct termios	termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
		error_exit("Tcgetattr failed\n", true);
	termios_current.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
		error_exit("Tcsetattr failed\n", true);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
