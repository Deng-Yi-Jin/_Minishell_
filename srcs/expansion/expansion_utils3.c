/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:56 by geibo             #+#    #+#             */
/*   Updated: 2024/10/02 16:06:37 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_value(char *env_key)
{
	t_env_var	*env_token;
	char		*env_value;

	env_token = find_env_vars(env_key);
	if (!env_token)
		return ("");
	env_value = env_token->value;
	return (env_value);
}

void	print_string_array(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		printf("split[%i] = [%s]\n", i, split[i]);
}
