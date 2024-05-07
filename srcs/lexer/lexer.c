/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2024/05/07 17:06:19 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

bool	error_return (t_token **tokens, char *input)
{
	t_token	*current_node;

	current_node = lst_go_back(*tokens);
	if (current_node->type == DOLLAR)
	{
		printf("syntax error near unexpected token `$'\n");
		free_stack(tokens, del, true, input);
		free(tokens);
		return (true);
	}
	while (current_node->next && current_node->next->type != 0)
		current_node = current_node->next;
	if (current_node->type == PIPE || current_node->type == 0)
	{
		printf("syntax error near unexpected token `|'\n");
		free_stack(tokens, del, true, input);
		free(tokens);
		return (true);
	}
	else if (current_node->type == OR)
	{
		printf("syntax error near unexpected token `||'\n");
		free_stack(tokens, del, true, input);
		free(tokens);
		return (true);
	}
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
	else if (input[*i] == '{')
		quoting(input, i, count_words, '}');
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
	int		i;
	char	*tempstring;
	char	*working;

	i = 0;
	tempstring = NULL;
	tempstring = dquote(input);
	if (tempstring)
		working = tempstring;
	else
		working = input;
	tokens = (t_token **)malloc(sizeof(t_token *));
	(*tokens) = NULL;
	while (working[i])
	{
		count_words = 0;
		while (working[i] == ' ' || working[i] == '\t')
			i++;
		lexing(working, tokens, &i, &count_words);
	}
	(*tokens) = add_null_token(*tokens);
	(*tokens) = lst_go_back(*tokens);
	if (error_return(tokens, working))
	{
		if (tempstring)
			free(tempstring);
		return ;
	}
	if (tempstring)
		free(tempstring);
	expand_dollar(tokens);
	parse(tokens, envp);
	free_stack(tokens, del, true, NULL);
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
