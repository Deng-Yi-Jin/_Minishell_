/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:21:02 by codespace         #+#    #+#             */
/*   Updated: 2023/08/20 12:34:52 by sinlee           ###   ########.fr       */
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

static void init_env(char **envp)
{
	int		i;
	char	*ms_path;

	i = -1;
	ms_path = ft_malloc(PATH_MAX);
	ft_snprintf(ms_path, PATH_MAX, "SHELL=%s/minishell", getenv("PWD"));
	envp[find_env("SHELL", envp)] = ms_path;
	g_main->env_vars = dup_darr(envp);
	add_env_vars(ft_strdup("NUM_QUOTES"), ft_strdup("0"));
	add_env_vars(ft_strdup("QUOTES"), ft_strdup("0"));
	add_env_vars(ft_strdup("PWD_MALLOC"), ft_strdup("0"));
	// add_env_vars(ft_strdup("TEST"), ft_strdup("123"));
}

void	init(char **envp)
{
	// g_num_env_vars = 0;
	g_main = malloc(sizeof(t_main));
	init_env(envp);
	init_signals();
	welcome_msg();
}
