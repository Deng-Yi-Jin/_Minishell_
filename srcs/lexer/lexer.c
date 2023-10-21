/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:34 by sinlee            #+#    #+#             */
/*   Updated: 2023/10/21 15:50:40 by root             ###   ########.fr       */
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
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (ft_symbol(input[i]) == false && input[i])
		{
			j = i;
			while (ft_symbol(input[i]) == false && input[i])
			{
				i++;
				count_words++;
			}
			(*tokens) = add_tokens((*tokens), ft_substr(input, j, count_words), WORD);
		}
		if (input[i] == '>' || input[i] == '<')
		{
			ft_redir(input, &i, tokens);
		}
		else if (input[i] == '|')
		{
			ft_pipe(input, &i, tokens);
		}
	}
	(*tokens) = add_null_token(*tokens);
	parse(tokens);
	// print_stack(*tokens);
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
