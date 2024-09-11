/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:37:26 by kytan             #+#    #+#             */
/*   Updated: 2024/09/11 09:27:05 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_expansion_needed(char *s)
{
	return (!ft_strchr(s, '$') && !ft_strchr(s, '\"') && !ft_strchr(s, '\''));
}

char	*full_expansion(char **split, int sep)
{
	char	*output;
	int		i;

	i = -1;
	output = ft_calloc(1, sizeof(char));
	while (split[++i])
	{
		output = ft_strfjoin(output, split[i]);
		if (split[i + 1] != NULL && sep)
			output = ft_strfjoin(output, " ");
	}
	free_split(split);
	return (output);
}

char	*dollar_q_expansion(char **split_q, char *s)
{
	char		*output;
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	while (split_q[++i])
	{
		flag = exp_flag(s, split_q[i]);
		// printf("flag for [%s] = %i\n", split_q[i], flag);
		if (flag == 0 && ft_strchr(split_q[i], '$'))
			split_q[i] = expanded(split_q[i]);
		s = ft_strchr(++s, '\'');
		// printf("\nfinding next (\')... %s\n", s);
	}
	output = full_expansion(split_q, 0);
	return (output);
}

char	*expansion(char **split)
{
	char	*output;
	char	*expanded;
	size_t	i;

	i = -1;
	while (split[++i])
	{
		if (no_expansion_needed(split[i]))
			continue ;
		else
		{
			expanded = dollar_q_expansion(ft_splitq(split[i], '\''), split[i]);
			free(split[i]);
			split[i] = expanded;
		}
	}
	output = full_expansion(split, 1);
	return (output);
}
