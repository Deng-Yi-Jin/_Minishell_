/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:48:47 by kytan             #+#    #+#             */
/*   Updated: 2024/09/27 10:26:03 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*valid_cmd_path(char *path, char *command)
{
	char	*token;
	char	full_path[PATH_MAX];

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



char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	*path;

	path_env = 0;
	if ((command[0] == '.' && command[1] == '/' && !access(command + 2, X_OK)))
		return (ft_strdup(command + 2));
	if (!access(command, X_OK))
		return (ft_strdup(command));
	if (find_env_vars("PATH"))
		path_env = find_env_vars("PATH")->value;
	if (path_env == NULL)
		return (NULL);
	path = ft_strdup(path_env);
	return (valid_cmd_path(path, command));
}

int	execute_builtin(char *inpt, char *args[N_ARGS], char **envp)
{
	if (!ft_strcmp(inpt, "exit"))
		exit_success();
	else if (!ft_strcmp(inpt, "cd"))
		return (execute_cd(args, envp));
	else if (!ft_strcmp(inpt, "fancy"))
		return (welcome_msg());
	else if (ft_strcmp(inpt, "export") == 0)
		return (execute_export(args));
	else if (ft_strcmp(inpt, "unset") == 0)
		return (execute_unset(args));
	else if (ft_strcmp(inpt, "echo") == 0)
		return (execute_echo(args));
	else if (ft_strcmp(inpt, "pwd") == 0)
		return (execute_pwd());
	else if (ft_strcmp(inpt, "env") == 0)
		return (execute_env(args));
	else
		return (1);
	return (0);
}

bool	is_builtin(char *command)
{
	if (!ft_strcmp(command, "exit") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "fancy") || !ft_strcmp(command, "quotes")
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env"))
		return (true);
	return (false);
}

int	is_command(char *cmd, char **envp)
{
	char	*command_path;

	if (is_builtin(cmd))
		return (CMD);
	command_path = find_command_path(cmd, g_main->envp);
	if (command_path != NULL)
	{
		free(command_path);
		return (CMD);
	}
	return (WORD);
}
