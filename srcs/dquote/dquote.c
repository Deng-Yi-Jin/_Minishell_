/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:30:20 by geibo             #+#    #+#             */
/*   Updated: 2024/05/08 14:42:18 by geibo            ###   ########.fr       */
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

bool	is_bracket(char c)
{
	return (c == ')' || c == ']' || c == '}');
}

char	*dquote(char *input)
{
	int		word;
	char	*temp;
	char	*output;
	char	**split;

	word = 0;
	split = ft_split(input, " ");
	output = NULL;
	while (split[word])
	{
		if (is_bracket(split[word][ft_strlen(split[word]) - 1]))
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				split[word][ft_strlen(split[word]) - 1]);
			free_split(split);
			return (NULL);
		}
		if (close_dquote(split[word]) == false)
		{
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
			temp = output;
			output = new_line(output, '\"');
			free(temp);
		}
		else if (close_squote(split[word]) == false)
		{
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
			temp = output;
			output = new_line(output, '\'');
			free(temp);
		}
		else
		{
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
		}
		word++;
	}
	free_split(split);
	if (output)
		return (output);
	return (NULL);
}
