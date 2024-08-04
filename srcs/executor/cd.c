/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sinlee <sinlee@student.42kl.edu.my>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/15 03:51:29 by codespace		 #+#	#+#			 */
/*   Updated: 2023/08/20 12:34:14 by sinlee		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

bool	execute_cd(char *args[N_ARGS], char **envp)
{
	char	*path;
	char	*ms_path;
	char	*tmp;

	if (args[1] == NULL || !ft_strcmp(args[1], "~"))
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(args[1]);
	if (chdir(path) != 0)
		perror_color("cd");
	modify_env_vars("PWD", getcwd(NULL, 0));
	ms_path = ft_malloc(PATH_MAX);
	ft_snprintf(ms_path, PATH_MAX, "PWD=%s", getcwd(NULL, 0));
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