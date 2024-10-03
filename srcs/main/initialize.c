/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:21:02 by codespace         #+#    #+#             */
/*   Updated: 2024/10/03 19:36:23 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_main	*g_main;

size_t	total_g_env_vars()
{
	size_t	size;

	size = 0;
	while (g_main->env_vars[size]->key != NULL)
		size++;
	return (size);
}

static void	init_env_vars(char **envp)
{
	char	*ms_path;
	int		i;

	ms_path = ft_malloc(PATH_MAX);
	ft_snprintf(ms_path, PATH_MAX, "SHELL=%s/minishell", getenv("PWD"));
	envp[find_env("SHELL", envp)] = ms_path;
	g_main->env_vars = dup_darr(envp);
	add_env_vars(ft_strdup("NUM_QUOTES"), ft_strdup("0"));
	add_env_vars(ft_strdup("QUOTES"), ft_strdup("0"));
	add_env_vars(ft_strdup("PWD_MALLOC"), ft_strdup("0"));
}

void	init(char **envp)
{
	g_main = ft_malloc(sizeof(t_main));
	g_main->nuclear_status = 0;
	init_env_vars(envp);
	init_signals();
	welcome_msg();
}

// void	print_g_envp()
// {
// 	int			i;

// 	i = -1;
// 	while (envp[++i] != NULL)
// 		printf("envp[%i] = %p [%s] \n", i, envp[i], envp[i]);
// 	if (envp[i] == NULL)
// 		printf("(NULL)");
// }