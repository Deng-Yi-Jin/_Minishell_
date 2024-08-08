/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:41:03 by sinlee            #+#    #+#             */
/*   Updated: 2024/04/01 18:19:34 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_vars(char *key, char *value)
{
	int			i;
	t_env_var	**new_env_vars;
	int			num_env_vars;

	if (key == NULL)
		perror_color("Environment Variables Name CANNOT be NULL!");
	num_env_vars = 0;
	while (g_main->env_vars[num_env_vars]->key != NULL)
		num_env_vars++;
	new_env_vars = (t_env_var **)ft_malloc((num_env_vars + 2)
			* sizeof(t_env_var *));
	i = -1;
	while (++i < num_env_vars)
	{
		new_env_vars[i] = malloc(sizeof(t_env_var));
		new_env_vars[i]->key = g_main->env_vars[i]->key;
		new_env_vars[i]->value = g_main->env_vars[i]->value;
	}
	new_env_vars[num_env_vars] = malloc(sizeof(t_env_var));
	new_env_vars[num_env_vars]->key = key;
	new_env_vars[num_env_vars]->value = value;
	new_env_vars[num_env_vars + 1] = malloc(sizeof(t_env_var));
	new_env_vars[num_env_vars + 1]->key = NULL;
	new_env_vars[num_env_vars + 1]->value = NULL;
	free_darr(g_main->env_vars);
	g_main->env_vars = new_env_vars;
}

void	modify_env_vars(char *key, char *value)
{
	t_env_var	*tmp;

	tmp = find_env_vars(key);
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = value;
	}
	else
		perror_color("Your environment variables does not exist.");
}
	// might add in find_env_vars instead

t_env_var	*find_env_vars(char *key)
{
	int	i;

	i = 0;
	while (g_main->env_vars[i]->key != NULL)
	{
		if (!ft_strcmp(g_main->env_vars[i]->key, key))
			break ;
		i++;
	}
	if (g_main->env_vars[i]->key == NULL)
		return (NULL);
	else
		return (g_main->env_vars[i]);
}

void	free_env_vars(void)
{
	int	i;

	i = -1;
	while (g_main->env_vars[++i]->key != NULL)
	{
		if (g_main->env_vars[i]->key != NULL)
			free(g_main->env_vars[i]->key);
		if (g_main->env_vars[i]->value != NULL)
			free(g_main->env_vars[i]->value);
	}
}

void	delete_env_vars(char *key)
{
	t_env_var	*tmp;

	tmp = find_env_vars(key);
	if (tmp != NULL)
	{
		free(tmp->value);
		free(tmp->key);
	}
	else
		perror_color("Your environment variables does not exist.");
	return ;
}
