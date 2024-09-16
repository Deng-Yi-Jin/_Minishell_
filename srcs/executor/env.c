/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:00:04 by kytan             #+#    #+#             */
/*   Updated: 2024/09/16 16:00:40 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(char **args)
{
	int	i;

	if (!args || args[1])
		return (false);
	i = 0;
	while (g_main->env_vars[i]->key != NULL)
	{
		printf("%s=%s\n", g_main->env_vars[i]->key, g_main->env_vars[i]->value);
		i++;
	}
}
