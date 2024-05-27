/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:58:35 by codespace         #+#    #+#             */
/*   Updated: 2024/05/27 16:38:18 by geibo            ###   ########.fr       */
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
	else if(ft_strcmp(inpt, "echo") == 0)
		execute_echo(args, is_flags(args)); // Flags here
	// else if (ft_strcmp(inpt, "unset"))
	//     ft_unset(envp);
	else
		return (false);
	return (true);
}

bool	is_builtin(char *command)
{
	if (!ft_strcmp(command, "exit") || !ft_strcmp(command, "cd")
	|| !ft_strcmp(command, "fancy") || !ft_strcmp(command, "quotes")
	|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset"))
		return (true);
	return (false);
}

int	is_command(char *cmd, char **envp)
{
	char	*command_path;

	command_path = find_command_path(cmd, envp);
	if (command_path != NULL)
	{
		free(command_path);
		return (CMD);
	}
	else if (command_path == NULL)
	{
		if (is_builtin(cmd))
			return (CMD);
	}
	return (WORD);
}
