/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2023/10/18 17:24:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

void	parse_input(char *input, char **envp)
{
	t_token **tokens;
	t_ast	*ast;
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
		j = i;
		while (input[i] && ft_symbol(input[i]) == false)
		{
			i++;
			count_words++;
		}
		(*tokens) = add_tokens((*tokens), ft_substr(input, j, count_words), WORD);
		if (input[i] == ' ')
			i++;
		else if (input[i] == '>' || input[i] == '<')
		{
			if (input[i] == '>' && input[i + 1] == '>')
			{
				(*tokens) = add_tokens((*tokens), ft_substr(input, i, 2), REDIR_OUT);
				i += 2;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				(*tokens) = add_tokens((*tokens), ft_substr(input, i, 2), REDIR_IN);
				i += 2;
			}
			else
			{
				(*tokens) = add_tokens((*tokens), ft_substr(input, i, 1), ft_return_op(input[i]));
				i++;
			}
		}
		else if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				(*tokens) = add_tokens((*tokens), ft_substr(input, i, 2), OR);
				i += 2;
			}
			else
			{
				(*tokens) = add_tokens((*tokens), ft_substr(input, i, 1), PIPE);
				i++;
			}
		}
	}
	(*tokens) = add_null_token(*tokens);
	// parse(tokens);
	print_stack(*tokens);
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
