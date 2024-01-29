/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:58:35 by codespace         #+#    #+#             */
/*   Updated: 2024/01/26 09:38:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	*path;
	char	*token;
    char    full_path[PATH_MAX];

	if ((command[0] == '.' && command[1] == '/' && !access(command+2, X_OK)))
		return (ft_strdup(command+2));
	if (!access(command, X_OK))
		return (ft_strdup(command));
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path = ft_strdup(path_env);
	token = strtok(path, ":");
	while (token != NULL)
	{
		ft_snprintf(full_path, PATH_MAX, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (ft_strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

bool	match_cmd(char *inpt, char *args[N_ARGS], char **envp)
{
	if (!ft_strcmp(inpt, "exit"))
		exit_success();
	else if (!ft_strcmp(inpt, "cd"))
		execute_cd(args, envp);
	else if (!ft_strcmp(inpt, "fancy"))
		welcome_msg();
	else if (!ft_strcmp(inpt, "quotes"))
		flip_bool_env_vars("QUOTES");
	else if (ft_strcmp(inpt, "export") == 0)
		execute_export(args);
	// else if (ft_strcmp(inpt, "unset"))
	//     ft_unset(envp);
	else
		return (false);
}
