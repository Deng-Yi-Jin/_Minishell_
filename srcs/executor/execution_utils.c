/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:39:04 by codespace         #+#    #+#             */
/*   Updated: 2024/01/29 05:35:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, char **envp)
{
	char	**path_env;
	char	*path_library;
	char	*path_cmd;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path_env = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_env[i])
	{
		path_library = ft_strjoin(path_env[i], "/");
		path_cmd = ft_strjoin(path_library, cmd);
		free(path_library);
		if (!access(path_cmd, F_OK))
		{
			ft_free_path_env(path_env);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_free_path_env(path_env);
	return (NULL);
}
		// printf("path_library: %s\n", path_library);

void	ft_free_path_env(char **path_env)
{
	int	i;

	i = 0;
	while (path_env[i])
		free(path_env[i++]);
	free(path_env);
}
