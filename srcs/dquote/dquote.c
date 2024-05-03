/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:30:20 by geibo             #+#    #+#             */
/*   Updated: 2024/05/03 13:34:45 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_line(char *input)
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
		if (ft_strlen(rl) > 0 && rl[ft_strlen(rl) - 1] == '\"' )
			break ;
		free(rl);
	}
	free(rl);
	return (output);
}

char	*dquote(char *input)
{
	int		i;
	char	*output;

	i = 0;
	output = NULL;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (!input[i] && input[i] != '\"')
				output = new_line(input);
		}
		else
			i++;
	}
	if (output)
	{
		return (output);
	}
	return (NULL);
}
