/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 07:05:53 by codespace         #+#    #+#             */
/*   Updated: 2023/08/15 12:17:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(const char *str)
{
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	for (size_t i = 1; i < ft_strlen(str); i++)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

bool	print_env_vars(void)
{
	// Print user-defined environment variables
	for (int i = 0; i < g_num_env_vars; i++)
	{
		printf("%s=%s\n", env_vars[i].name, env_vars[i].value);
	}
	// Print system environment variables
	for (int i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (true);
}

bool	execute_export(char **args)
{
	args++;
	char *name = ft_strdup(*args);
	char *value = ft_strchr(name, '=');

	if (value)
	{
		*value = '\0';
		value++;

		if (!is_valid_identifier(name))
		{
			printf("export: `%s': not a valid identifier\n", name);
			free(name);
			return (false);
		}

		for (int i = 0; i < g_num_env_vars; i++)
		{
			if (strcmp(env_vars[i].name, name) == 0)
			{
				free(env_vars[i].value);
				env_vars[i].value = ft_strdup(value);
				free(name);
				return (true);
			}
		}

		if (g_num_env_vars < MAX_ENV_VARS)
		{
			env_vars[g_num_env_vars].name = ft_strdup(name);
			env_vars[g_num_env_vars].value = ft_strdup(value);
			g_num_env_vars++;
			free(name);
			return (true);
		}
		else
		{
			printf("export: too many environment variables\n");
			free(name);
			return (false);
		}
	}
	else
	{
		printf("export: `%s': not a valid identifier\n", *args);
		free(name);
		return (false);
	}
}