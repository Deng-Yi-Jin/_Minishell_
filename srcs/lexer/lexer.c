/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/16 16:46:36 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	error_return(t_token **tokens, char *input)
{
	t_token	*current_node;

	current_node = lst_first_last(*tokens, false);
	if (check_first_token(current_node, tokens, input))
		return (true);
	if (check_consecutive_tokens(current_node, tokens, input))
		return (true);
	if (check_last_token(current_node, tokens, input))
		return (true);
	return (false);
}

void	dollar(char *input, int *i, int *count_words)
{
	int	j;

	j = *i;
	(*i)++;
	(*count_words)++;
	if (input[*i] == '(')
		quoting(input, i, count_words, ')');
	else if (input[*i] == '\"')
		quoting(input, i, count_words, '\"');
	else if (input[*i] == '\'')
		quoting(input, i, count_words, '\'');
	else if (input[*i] == '?')
	{
		(*i)++;
		(*count_words)++;
	}
	else
	{
		while (ft_symbol(input[*i]) == false && input[*i])
		{
			(*i)++;
			(*count_words)++;
		}
	}
}

void	quoting(char *str, int *i, int *count_words, char c)
{
	(*i)++;
	(*count_words)++;
	while (str[*i] != c && str[*i] != '\0')
	{
		(*i)++;
		(*count_words)++;
	}
	(*i)++;
	(*count_words)++;
}

void	parse_input(char *input, char **envp)
{
	t_token	**tokens;
	char	*tempstring;
	char	*working;

	tempstring = dquote(input);
	tempstring = trim_quotation(tempstring);
	working = tempstring;
	tokens = (t_token **)malloc(sizeof(t_token *));
	(*tokens) = NULL;
	start_lex(working, tokens);
	if (error_return(tokens, working))
	{
		if (tempstring)
			free(tempstring);
		return ;
	}
	if (tempstring)
		free(tempstring);
	parse(tokens, envp);
	free_stack(tokens, del, true, NULL);
	free(tokens);
}
