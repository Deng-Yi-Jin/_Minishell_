/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2024/03/05 15:19:18 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

void	dollar(char *input, int *i, int *count_words)
{
	int	j;

	j = *i;
	(*i)++;
	(*count_words)++;
	if (input[*i] == '(')
		quoting(input, i, count_words, ')');
	else if (input[*i] == '{')
		quoting(input, i, count_words, '}');
	else if (input[*i] == '\"')
		quoting(input, i, count_words, '\"');
	else if (input[*i] == '\'')
		quoting(input, i, count_words, '\'');
	else if (input[*i] == '[')
		quoting(input, i, count_words, ']');
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
		if (str[*i] == '$')
			dollar(str, i, count_words);
		else
		{
			(*i)++;
			(*count_words)++;
		}
	}
	(*i)++;
	(*count_words)++;
}


void	parse_input(char *input, char **envp, int count_words)
{
	t_token	**tokens;
	t_ast	*ast;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tokens = (t_token **)malloc(sizeof(t_token *));
	(*tokens) = NULL;
	while (input[i])
	{
		count_words = 0;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		lexing(input, tokens, &i, &count_words);
	}
	(*tokens) = add_null_token(*tokens);
	(*tokens) = lst_go_back(*tokens);
	expand_dollar(tokens);
	parse(tokens, envp);
	free_stack(tokens, del, true);
	free(tokens);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;

// 	while (1)
// 	{
// 		input = readline("minishell$: ");
// 		parse_input(input, envp);
// 		free(input);
// 	}
// 	return (0);
// }
