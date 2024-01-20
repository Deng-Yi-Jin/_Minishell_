/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2024/01/18 03:24:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

//char	*dquote(char *str)
//{
//	int		i;
//	char	*tmp;

//	tmp = str;
//	i = 0;
//	while (tmp[i] != NULL)
//}

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


void	parse_input(char *input, char **envp)
{
	t_token **tokens;
	t_ast	*ast;
	char	*tmp;
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
		if (input[i] == '$')
		{
			j = i;
			dollar(input, &i, &count_words);
			(*tokens) = add_tokens((*tokens), ft_substr(input, j, count_words + 1), DOLLAR);
		}
		if (ft_symbol(input[i]) == false && input[i])
		{
			j = i;
			while (ft_symbol(input[i]) == false && input[i])
			{
				if (input[i] == '\'')
					quoting(input, &i, &count_words, '\'');
				else if (input[i] == '\"')
					quoting(input, &i, &count_words, '\"');
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
			ft_pipe(input, &i, tokens);
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
