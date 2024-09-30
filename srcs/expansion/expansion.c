/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:37:26 by kytan             #+#    #+#             */
/*   Updated: 2024/09/30 14:03:18 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_expansion_needed(char *s)
{
	return (!ft_strchr(s, '$') && !ft_strchr(s, '\"') && !ft_strchr(s, '\''));
}

char	*full_expansion(char **split, char *sep)
{
	char	*output;
	int		i;

	i = -1;
	output = ft_calloc(1, sizeof(char));
	while (split[++i])
	{
		output = ft_strfjoin(output, split[i]);
		if (split[i + 1] != NULL && sep)
			output = ft_strfjoin(output, sep);
	}
	return (output);
}

char	*dollar_q_expansion(char **split_q)
{
	char	*output;
	int		i;

	i = -1;
	while (split_q[++i])
	{
		if (ft_strchr(split_q[i], '$'))
			split_q[i] = expanded(split_q[i]);
	}
	output = full_expansion(split_q, " ");
	free_split(split_q);
	return (output);
}
