/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:27:48 by kytan             #+#    #+#             */
/*   Updated: 2024/09/08 11:35:46 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_cd(char *args[N_ARGS], char **envp)
{
	char	*path;
	char	*ms_path;
	char	*tmp;
	char	*cwd;

	if (args[1] == NULL || !ft_strcmp(args[1], "~"))
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(args[1]);
	if (chdir(path) != 0)
		perror_color("cd");
	modify_env_vars("PWD", getcwd(NULL, 0));
	ms_path = ft_malloc(PATH_MAX);
	cwd = getcwd(NULL, 0);
	ft_snprintf(ms_path, PATH_MAX, "PWD=%s", cwd);
	free(cwd);
	if ((ft_strcmp(find_env_vars("PWD_MALLOC")->value, "1") == 0))
	{
		tmp = envp[find_env("PWD", envp)];
		envp[find_env("PWD", envp)] = ms_path;
		free(tmp);
	}
	else
	{
		envp[find_env("PWD", envp)] = ms_path;
		modify_env_vars("PWD_MALLOC", ft_strdup("1"));
	}
	free(path);
	return (true);
}
