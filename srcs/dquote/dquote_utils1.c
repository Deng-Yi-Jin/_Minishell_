/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:53:49 by kytan             #+#    #+#             */
/*   Updated: 2024/08/14 16:55:22 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_line(char *input, char c)
{
	char	*rl;
	char	*output;
	char	*tmp;

	output = ft_strdup(input);
	while (1)
	{
		rl = readline("> ");
		if (!rl)
		{
			free(output);
			return (input);
		}
		output = ft_strjoin(output, "\n");
		output = ft_strjoin(output, rl);
		if (ft_strlen(rl) > 0 && rl[ft_strlen(rl) - 1] == c)
			break ;
		free(rl);
	}
	free(rl);
	return (output);
}

bool	is_bracket(char c)
{
	return (c == ')' || c == '(');
}

char	*error_bracket(char	**split, int word)
{
	printf("minishell: syntax error near unexpected token `%c'\n",
		split[word][ft_strlen(split[word]) - 1]);
	free_split(split);
	return (NULL);
}
