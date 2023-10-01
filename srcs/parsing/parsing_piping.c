/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:34:26 by root              #+#    #+#             */
/*   Updated: 2023/09/25 20:02:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_ast	**parse_piping(t_token **tokens, t_ast **ast)
// {
	
// }

// int	quote_checker(t_token **tokens)
// {
// 	while (*tokens)
// 	{
// 		if ((*tokens)->type == BOO_NO_EXPANSION)
// 			return (1);
// 		else if ((*tokens)->type == DOMESTIC_EXPANSION)
// 			return (2);
// 		*tokens = (*tokens)->next;			
// 	}
// 	return (0);
// }

// t_ast	*add_ast(t_ast *ast, t_token *token)
// {
// 	t_ast	*new_node;
// 	t_ast	*tmp;

// 	new_node = create_ast_node(token->cmd);
// 	if (!ast)
// 		return (new_node);
// 	tmp = ast;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new_node;
// 	return (ast);
// }



char	*ast_strjoin(t_token **tokens, char *str)
{
	if ((*tokens)->type == MINUS && (*tokens)->next->type == WORD)
	{
		str = ft_strjoin((*tokens)->cmd, (*tokens)->next->cmd);
		*tokens = (*tokens)->next->next;
	}
	else if ((*tokens)->type == WORD)
	{
		str = ft_strdup((*tokens)->cmd);
		(*tokens) = (*tokens)->next;
	}
	return	(str);
}
