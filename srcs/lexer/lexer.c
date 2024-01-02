/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2024/01/02 04:42:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

void	quoting(char *input, int *i, int *count_words, char quote)
{
	(*i)++;
	(*count_words)++;
	while (input[*i] != quote && input[*i])
	{
		(*i)++;
		(*count_words)++;
	}
	if (input[*i] == quote)
	{
		(*i)++;
		(*count_words)++;
	}
}

void	dollar(char *input, int *i, int *count_words)
{
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

void	parse_input(char *input, char **envp)
{
	t_token **tokens;
	t_ast	*ast;
	char	*tmp;
	int		double_quote;
	int		single_quote;
	int		i;
	int		j;
	int		count_words;

	i = 0;
	j = 0;
	tokens = (t_token **)malloc(sizeof(t_token *));
	(*tokens) = NULL;
	// printf("tokens->firstaddress %p\n", (*tokens));
	while (input[i])
	{
		count_words = 0;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (ft_symbol(input[i]) == false && input[i])
		{
			j = i;
			while (ft_symbol(input[i]) == false && input[i])
			{
				if (input[i] == '\'')
					quoting(input, &i, &count_words, '\'');
				else if (input[i] == '\"')
					quoting(input, &i, &count_words, '\"');
				else if (input[i] == '$')
				{
					dollar(input, &i, &count_words);
				}
				else
				{
					i++;
					count_words++;
				}
			}
			(*tokens) = add_tokens((*tokens), ft_substr(input, j, count_words), WORD);
		}
		if (input[i] == '>' || input[i] == '<')
			ft_redir(input, &i, tokens);
		else if (input[i] == '|')
		{
			ft_pipe(input, &i, tokens);
		}
	}
	(*tokens) = add_null_token(*tokens);
	parse(tokens);
	//print_stack(*tokens);
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
