/* ************************************************************************** */
/*					*/
/*				:::			::::::::	 */
/*	 env.c					:+:			:+:		:+:	 */
/*					+:+ +:+				 +:+		 */
/*	 By: kytan <kytan@student.42kl.edu.my>					+#+	+:+			 +#+				*/
/*			+#+#+#+#+#+	 +#+					 */
/*	 Created: 2023/08/16 16:41:03 by sinlee			#+#		#+#			 */
/*	 Updated: 2024/09/07 18:38:00 by kytan			###	 ########.fr			 */
/*					*/
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
	t_env_var	*unset;

	unset = find_env_vars(key);
	if (unset != NULL)
	{
		free(unset->value);
		unset->value = value;
	}
	else
		perror_color("Your environment variables does not exist.");
}

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

size_t	new_vars_ct(char *unset_key)
{
	int i;
	size_t env_ct;

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

void	delete_env_vars(char *key)
{
	t_env_var	*unset;
	t_env_var	**new;
	int i;
	int j;

	i = -1;
	j = 0;
	unset = find_env_vars(key);
	if (unset == NULL)
		return ;
	new = (t_env_var **)ft_malloc(new_vars_ct(unset->key) * sizeof(t_env_var *));
	while (g_main->env_vars[++i]->key != NULL)
	{
		if (!ft_strcmp(g_main->env_vars[i]->key, unset->key))
		{
			free(g_main->env_vars[i]->key);
			free(g_main->env_vars[i]->value);
			continue ;
		}
		new[j] = (t_env_var *)ft_malloc(sizeof(t_env_var));
		new[j]->key = g_main->env_vars[i]->key;
		new[j++]->value = g_main->env_vars[i]->value;
	}
	new[j] = ft_calloc(1, sizeof(t_env_var));
	free_darr(g_main->env_vars);
	g_main->env_vars = new;
}

/* KYLIE TINKERED WITH 5:56PM 8/14/2024

split add_env_vars(): added init_new_env_var()

*/
/*
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
	init_new_env_var(new_env_vars, num_env_vars, key, value);
	// new_env_vars[num_env_vars] = malloc(sizeof(t_env_var));
	// new_env_vars[num_env_vars]->key = key;
	// new_env_vars[num_env_vars]->value = value;
	// new_env_vars[num_env_vars + 1] = malloc(sizeof(t_env_var));
	// new_env_vars[num_env_vars + 1]->key = NULL;
	// new_env_vars[num_env_vars + 1]->value = NULL;
	free_darr(g_main->env_vars);
	g_main->env_vars = new_env_vars;
}*/