/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:06:55 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/15 16:51:22 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(char **args)
{
	int	i;

	i = -1;
	if (!args || !args[1])
		return (1);
	while (args[++i] != NULL)
		delete_env_vars(args[i]);
	return (0);
}
