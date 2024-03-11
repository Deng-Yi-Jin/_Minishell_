/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:34 by djin              #+#    #+#             */
/*   Updated: 2024/03/07 19:39:43 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_print(void *cmd)
{
	ft_printf("%s", (char *)cmd);
}



void	parse(t_token **tokens, char **envp)
{
	t_ast	**ast;
	t_ast	*minishell;
	t_exec	*exec;

	(*tokens) = lst_first_last(*tokens, false);
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	(*ast) = create_parent_node(NULL);
	minishell = (*ast);
	start_parse(ast, tokens);
	while ((*ast)->parent != NULL)
		(*ast) = (*ast)->parent;
	
	minishell = (*ast);
	exec = executing(ast, exec);
	execute(exec, envp);
	free_exec(exec);
	(*ast) = minishell;
	traverse(ast, free, 0, false);
	free(ast);
}