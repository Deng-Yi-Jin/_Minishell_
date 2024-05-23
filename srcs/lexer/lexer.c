/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2024/05/21 10:10:52 by geibo            ###   ########.fr       */
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
	char	*tempstring;
	char	*working;
	char	*temp;

	temp = expand_dollar(input);
	if (temp == NULL)
		return ;
	tempstring = dquote(temp);
	if (tempstring == NULL)
	{
		free(temp);
		return ;
	}
	working = tempstring;
	tokens = (t_token **)malloc(sizeof(t_token *));
	(*tokens) = NULL;
	start_lex(working, tokens);
	if (error_return(tokens, working))
	{
		if (tempstring)
			free(tempstring);
		free(temp);
		return ;
	}
	if (tempstring)
		free(tempstring);
	parse(tokens, envp);
	free_stack(tokens, del, true, NULL);
	free(temp);
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
