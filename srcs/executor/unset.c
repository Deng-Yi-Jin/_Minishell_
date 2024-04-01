/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:06:55 by sinlee            #+#    #+#             */
/*   Updated: 2024/04/01 18:20:59 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute_unset(char **args){
	int i;

	i = -1;
	if (args[1] == NULL)
		return ;
	else 
	{
		while (args[++i] != NULL)
			delete_env_vars(args[i]);
	}
	return ;
}