/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:37:26 by kytan             #+#    #+#             */
/*   Updated: 2024/10/02 15:28:14 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_dollar_env(char *env_v, char *output, int *j, size_t size)
{
	char			*start;
	char			*env_key;
	char			*env_val;

	if (!env_v || !env_v[0])
		return (0);
	if (*env_v == '$' && *(env_v + 1) == '?')
	{
		env_v += 2;
		*j += snprintf(output, size - *j, "%i", g_main->nuclear_status);
		return (env_v);
	}
	if (*env_v == '$')
		env_v++;
	start = env_v;
	while (ft_isalnum(*env_v) && *env_v)
		env_v++;
	env_key = extract_key(start);
	env_val = extract_value(env_key);
	free(env_key);
	if (env_val[0] && env_val)
		*j += snprintf(output, size - *j, "%s", env_val);
	else
		*j += snprintf(output, size - *j, "$");
	return (env_v);
}

char	*cp_to_expanded(char *split_q, char *output, size_t size)
{
	int		j;

	j = 0;
	while (*split_q)
	{
		if (*split_q == '$' && *(split_q + 1))
			split_q = exp_dollar_env(split_q, output + j, &j, size);
		else
			output[j++] = *split_q++;
	}
	return (output);
}

char	*expanded(char *split_q)
{
	char	*output;
	size_t	size;

	size = calc_envsize(split_q);
	output = ft_calloc(size + 1, sizeof(char));
	output = cp_to_expanded(split_q, output, size + 1);
	free(split_q);
	return (output);
}
