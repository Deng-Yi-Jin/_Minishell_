/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:01:17 by codespace         #+#    #+#             */
/*   Updated: 2024/10/03 20:01:57 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main	*g_main;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	prompt[LOGIN_NAME_MAX + PATH_MAX + 20];

	if (argc != 1 || argv[1])
		error_exit("Error: too many arguments\n", false);
	init(envp);
	while (1)
	{
		input = readline(prompt_msg(prompt));
		if (!input || ft_strcmp(input, "exit") == 0)
			execute_exit(EXIT_SUCCESS);
		if (input[0] != '\0')
		{
			add_history(input);
			parse_input(input, envp);
		}
		free(input);
	}
	return (123);
}
