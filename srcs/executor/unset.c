/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:06:55 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/16 03:27:29 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(char **args)
{
	int	i;

	i = -1;
	if (!args || !args[1])
		return (EXIT_FAILURE);
	while (args[++i] != NULL)
		delete_env_vars(args[i]);
	return (EXIT_SUCCESS);
}
