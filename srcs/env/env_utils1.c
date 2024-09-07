/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:08:30 by kytan             #+#    #+#             */
/*   Updated: 2024/09/07 14:08:09 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_new_env_var(t_env_var **new_env_vars, int num_env_vars, char *key,
		char *value)
{
	new_env_vars[num_env_vars] = malloc(sizeof(t_env_var));
	new_env_vars[num_env_vars]->key = key;
	new_env_vars[num_env_vars]->value = value;
	new_env_vars[num_env_vars + 1] = malloc(sizeof(t_env_var));
	new_env_vars[num_env_vars + 1]->key = NULL;
	new_env_vars[num_env_vars + 1]->value = NULL;
}
