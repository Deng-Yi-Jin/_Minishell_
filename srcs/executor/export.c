/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:32:57 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/26 15:44:10 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(const char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (str[++i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

void	print_env_vars(void)
{
	int	i;

	i = -1;
	while (g_main->env_vars[++i]->key != NULL)
		printf("declare -x %s=\"%s\"\n", g_main->env_vars[i]->key,
			g_main->env_vars[i]->value);
}

void	export_env(char *key, char *value)
{
	if (find_env_vars(key) != NULL)
		modify_env_vars(key, ft_strdup(value));
	else
		add_env_vars(ft_strdup(key), ft_strdup(value));
}

int	exec_export(char **args)
{
	int		i;
	char	*ptr;

	i = 0;
	while (args[++i] != NULL)
	{
		ptr = ft_strchr(args[i], '=');
		if (ptr)
		{
			*ptr = '\0';
			ptr++;
			if (!is_valid_identifier(args[i]))
			{
				printf("%sexport: `%s': not a valid identifier\n%s", RED,
					args[i], RESET_COLOR);
				return (EXIT_FAILURE);
			}
			export_env(args[i], ptr);
		}
		else
			export_env(args[i], "");
	}
	update_g_envp();
}

int	execute_export(char **args)
{
	if (args[1] == NULL)
		print_env_vars();
	else
		return (exec_export(args));
	return (EXIT_SUCCESS);
}
