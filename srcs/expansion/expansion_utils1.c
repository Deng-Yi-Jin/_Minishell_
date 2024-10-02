/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:42:02 by kytan             #+#    #+#             */
/*   Updated: 2024/09/29 21:29:35 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	calc_envlen(char *s, int *i)
{
	int			j;
	char		*env_key;
	t_env_var	*env_token;
	size_t		envlen;
	char			*exit_status;

	if (s[*i] == '$')
	{
		(*i)++;
		envlen = 0;
		if (s[*i] == '?')
		{
			(*i)++;
			exit_status = ft_itoa(g_main->nuclear_status);
			j = ft_strlen(exit_status);
			free(exit_status);
			return (j);
		}
	}
	j = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	env_key = ft_substr(s, (unsigned int)j, (size_t)(*i - j));
	env_token = find_env_vars(env_key);
	if (env_token)
		envlen += ft_strlen(env_token->value);
	free(env_key);
	return (envlen);
}

size_t	calc_envsize(char *split_q)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (split_q[i])
	{
		if (split_q[i] == '$' && split_q[i + 1])
			size += calc_envlen(split_q, &i);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

char	*extract_key(char *env_s)
{
	char	*start;
	char	*extract;

	if (!env_s || !env_s[0])
		return (0);
	if (*env_s == '$')
		env_s++;
	start = env_s;
	while (*env_s && ft_isalnum(*env_s))
		env_s++;
	extract = ft_strldup(start, (env_s - start) + 1);
	return (extract);
}

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
