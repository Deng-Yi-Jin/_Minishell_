/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:56:56 by sinlee            #+#    #+#             */
/*   Updated: 2024/10/03 21:06:17 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_exit_status(int *i, char *string)
{
	ft_putnbr_fd(g_main->nuclear_status, 1);
	*i += 2;
}

void	echo_char(char c)
{
	if (!c)
		return ;
	ft_putchar_fd(c, 1);
}

void	echo_args(char **args)
{
	int		i;
	int		j;
	char	*string;

	i = -1;
	while (args[++i])
	{
		string = args[i];
		j = 0;
		if (i != 0)
			echo_char(' ');
		while (string[j])
		{
			if (ft_strncmp(string + j, "$?", 2) == 0)
				echo_exit_status(&j, string);
			else if (string[j] == '\'')
				j++;
			else
				echo_char(string[j++]);
		}
	}
}

int	execute_echo(char **args)
{
	int		i;
	int		j;
	bool	n_flag;
	char	*single_arg_str;

	i = 1;
	n_flag = false;
	if (args && args[i])
	{
		while (ft_strncmp(args[i], "-n", 2) == 0)
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] != '\0')
				break ;
			n_flag = true;
			i++;
		}
		if (args[i])
			echo_args(args + i);
	}
	if (n_flag == false)
		printf("\n");
	return (EXIT_SUCCESS);
}
