/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:36:55 by djin              #+#    #+#             */
/*   Updated: 2024/03/12 02:27:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_parse(t_ast **ast, t_token **tokens, char **envp)
{
	while ((*tokens)->cmd != NULL)
	{
		form_ast(ast, tokens, envp);
		if ((*tokens)->type == PIPE)
		{
			(*ast) = (*ast)->parent;
			(*tokens) = (*tokens)->next;
		}
	}
}

void	form_ast(t_ast **ast, t_token **tokens, char **envp)
{
	char	*tmp;
	bool	is_c;
	bool	create_s;	

	is_c = true;
	create_s = false;
	tmp = ft_calloc(1, sizeof(char));
	while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
	{
		tmp = ft_strjoin(tmp, (*tokens)->cmd);
		(*tokens) = (*tokens)->next;
	}
	*tokens = lst_go_back(*tokens);
	while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
	{
		if (is_c && (*tokens)->prev && (*tokens)->prev->type == PIPE)
			construct_child_after_pipe(ast, tmp, &is_c);
		else if (is_c == true)
			construct_child_before_pipe(ast, tmp, &is_c);
		if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL && is_c == false)
		{
			construct_sibling(ast, tokens, &create_s, envp);
			(*tokens) = (*tokens)->next;
		}
	}
}
