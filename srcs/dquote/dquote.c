/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:30:20 by geibo             #+#    #+#             */
/*   Updated: 2024/09/04 14:28:01 by geibo            ###   ########.fr       */
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

void	handle_quote(char **split, int word, char *output, char c)
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
}

// char	*dquote(char *input)
// {
// 	int		word;
// 	char	*output;
// 	char	**split;

// 	word = 0;
// 	split = ft_split(input, " ");
// 	output = NULL;
// 	while (split[word])
// 	{
// 		if (is_bracket(split[word][ft_strlen(split[word]) - 1]))
// 			return (error_bracket(split, word));
// 		if (close_dquote(split[word]) == false)
// 			handle_quote(split, word, output, '\"');
// 		else if (close_squote(split[word]) == false)
// 			handle_quote(split, word, output, '\'');
// 		else
// 			handle_quote(split, word, output, '\0');
// 		word++;
// 	}
// 	free_split(split);
// 	if (output)
// 		return (output);
// 	return (NULL);
// }

/* KYLIE TINKERED WITH 4:35PM 8/14/2024

split dquote(): added handle_quote(), error_bracket()
created dquote_utils1.c;
*/

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
		// if (is_bracket(split[word][ft_strlen(split[word]) - 1]))
		// 	// return (error_bracket(split, word));
		// {
		// 	printf("minishell: syntax error near unexpected token `%c'\n",
		// 		split[word][ft_strlen(split[word]) - 1]);
		// 	free_split(split);
		// 	return (NULL);
		// }
		if (close_dquote(split[word]) == false)
			// handle_quote(split, word, output, '\"');
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
			// handle_quote(split, word, output, '\'');
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
			// handle_quote(split, word, output, '\0');
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

// bool	is_bracket(char c)
// {
// 	return (c == ')' || c == '(');
