/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:21:02 by codespace         #+#    #+#             */
/*   Updated: 2024/05/03 10:38:51 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	implement_tools(t_tools *tools)
// {
// 	tools->args = NULL;
// 	tools->paths = NULL;
// 	tools->simple_cmds = NULL;
// 	tools->lexer_list = NULL;
// 	tools->pwd = NULL;
// 	tools->old_pwd = NULL;
// 	tools->pipes = 0;
// 	tools->pid = NULL;
// 	tools->heredoc = false;
// 	tools->reset = false;
// }

static void	init_env(char **envp)
{
	char	*ms_path;

	ms_path = ft_malloc(PATH_MAX);
	ft_snprintf(ms_path, PATH_MAX, "SHELL=%s/minishell", getenv("PWD"));
	envp[find_env("SHELL", envp)] = ms_path;
	g_main->env_vars = dup_darr(envp);
	add_env_vars(ft_strdup("NUM_QUOTES"), ft_strdup("0"));
	add_env_vars(ft_strdup("QUOTES"), ft_strdup("0"));
	add_env_vars(ft_strdup("PWD_MALLOC"), ft_strdup("0"));
}
	// add_env_vars(ft_strdup("TEST"), ft_strdup("123"));

// g_num_env_vars = 0;
void	init(char **envp)
{
	g_main = malloc(sizeof(t_main));
	init_env(envp);
	init_signals();
	welcome_msg();
}
