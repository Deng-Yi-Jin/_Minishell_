/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:30:20 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 13:52:18 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	close_squote(char *input)
{
	int		i;
	int		quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			quote++;
		else if (quote % 2 == 0 && input[i])
			quote = 0;
		i++;
	}
	if (quote % 2 == 0 || quote == 0)
		return (true);
	return (false);
}

bool	close_dquote(char *input)
{
	int		i;
	int		quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			quote++;
		else if (quote % 2 == 0 && input[i])
			quote = 0;
		i++;
	}
	if (quote % 2 == 0 || quote == 0)
		return (true);
	return (false);
}

char	*handle_quote(char **split, int word, char *output, char c)
{
	char	*temp;

	temp = output;
	if (output == NULL)
		output = ft_strdup(split[word]);
	else
		output = ft_strjoin(output, split[word]);
	free(temp);
	if (split[word + 1] != NULL)
	{
		temp = output;
		output = ft_strjoin(output, " ");
		free(temp);
	}
	if (c == '\"' || c == '\'')
	{
		temp = output;
		output = new_line(output, c);
		free(temp);
	}
	return (output);
}

char	*dquote(char *input)
{
	int		word;
	char	*output;
	char	**split;

	word = 0;
	split = ft_split(input, " ");
	output = NULL;
	while (split[word])
	{
		if (close_dquote(split[word]) == false)
			output = handle_quote(split, word, output, '\"');
		else if (close_squote(split[word]) == false)
			output = handle_quote(split, word, output, '\'');
		else
			output = handle_quote(split, word, output, '0');
		word++;
	}
	free_split(split);
	return (output);
}
