/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:08:30 by kytan             #+#    #+#             */
/*   Updated: 2024/09/16 13:28:12 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_new_env_var(t_env_var **new_env_vars, int num_env_vars,
			char *key, char *value)
{
	new_env_vars[num_env_vars] = malloc(sizeof(t_env_var));
	new_env_vars[num_env_vars]->key = key;
	new_env_vars[num_env_vars]->value = value;
}

void	init_null_env_var(t_env_var **new_env_vars, int num_env_vars,
			char *key, char *value)
{
	new_env_vars[num_env_vars + 1] = ft_calloc(1, sizeof(t_env_var));
}

size_t	new_vars_ct(char *unset_key)
{
	size_t	env_ct;
	int		i;

	i = -1;
	env_ct = 0;
	while (g_main->env_vars[++i]->key != NULL)
	{
		if (!ft_strcmp(g_main->env_vars[i]->key, unset_key))
			continue ;
		env_ct++;
	}
	if (g_main->env_vars[i])
		env_ct++;
	return (env_ct);
}
