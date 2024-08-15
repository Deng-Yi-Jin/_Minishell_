/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 02:29:43 by codespace         #+#    #+#             */
/*   Updated: 2023/08/19 22:58:04 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// printf("QUOTES: %s", find_env_vars("QUOTES").value);
char	*prompt_msg(char prompt[LOGIN_NAME_MAX + PATH_MAX + 20])
{
	char	*username;
	char	cwd[PATH_MAX];

	username = getenv("USER");
	if (username == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	ft_snprintf(prompt, (LOGIN_NAME_MAX + PATH_MAX + 20),
		"\033[0;35m@%s %s-> %s%s%s $ %s",
		username, RESET_COLOR, BLUE_BOLD, cwd, RESET_COLOR, CYAN);
	return (prompt);
}
	// if (!ft_strcmp(find_env_vars("QUOTES")->value, "1"))
		// prompt_quotes(prompt);
