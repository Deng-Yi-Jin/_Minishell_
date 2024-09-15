/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:42:02 by kytan             #+#    #+#             */
/*   Updated: 2024/09/15 19:11:08 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	calc_envlen(char *s, int *i)
{
	int				j;
	char			*env_key;
	t_env_var	*env_token;
	size_t		envlen;

	if (s[*i] == '$')
	{
		(*i)++;
		envlen = 1;
	}
	j = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	env_key = ft_substr(s, (unsigned int)j,(size_t)(*i - j));
	env_token = find_env_vars(env_key);
	// if (!env_token)
	// 	envlen = 1;
	// else
	if (env_token)
		envlen += ft_strlen(env_token->value);
	free(env_key);
	return (envlen);
}

size_t	calc_envsize(char *split_q)
{
	int			i;
	size_t	size;

	i = 0;
	size = 0;
	while (split_q[i])
	{
		if (split_q[i] == '$')
			size += calc_envlen(split_q, &i);
		else if (split_q[i] != '$')
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
	// printf("extract = %s\n", extract);
	return (extract);
}

char	*extract_value(char *env_key)
{
	t_env_var	*env_token;
	char			*env_value;

	env_token = find_env_vars(env_key);
	if (!env_token)
		return ("");
	env_value = env_token->value;
	// printf("env_val = %s\n", env_value);
	return (env_value);
}