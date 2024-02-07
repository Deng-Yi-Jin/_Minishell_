/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djin <djin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:01:17 by codespace         #+#    #+#             */
/*   Updated: 2024/02/06 12:44:58 by djin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main file for minishell project, which is a recreation of the bash shell

#include "minishell.h"

t_main *g_main;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	prompt[LOGIN_NAME_MAX + PATH_MAX + 20];

	if (argc != 1 || argv[1])
		error_exit("Error: too many arguments\n", false);
	init(envp);
	//test_traverse();
	while (1)
	{
		input = readline(prompt_msg(prompt));
		if (!input || strcmp(input, "exit") == 0)
			exit_success();
		if (input[0] != '\0')
		{
			add_history(input);
			parse_input(input, envp, 0);
		}
		free(input);
	}
	return (0);
}
