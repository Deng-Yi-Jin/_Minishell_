/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:42:02 by kytan             #+#    #+#             */
/*   Updated: 2024/10/02 15:45:12 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	handle_exit_status(int *i)
{
	char	*exit_status;
	size_t	len;

	(*i)++;
	exit_status = ft_itoa(g_main->nuclear_status);
	len = ft_strlen(exit_status);
	free(exit_status);
	return (len);
}

static size_t	handle_env_var(char *s, int *i)
{
	int			j;
	char		*env_key;
	t_env_var	*env_token;
	size_t		envlen;

	j = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	env_key = ft_substr(s, (unsigned int)j, (size_t)(*i - j));
	env_token = find_env_vars(env_key);
	envlen = 0;
	if (env_token)
		envlen = ft_strlen(env_token->value);
	free(env_key);
	return (envlen);
}

size_t	calc_envlen(char *s, int *i)
{
	if (s[*i] == '$')
	{
		(*i)++;
		if (s[*i] == '?')
			return (handle_exit_status(i));
		return (handle_env_var(s, i));
	}
	return (0);
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
