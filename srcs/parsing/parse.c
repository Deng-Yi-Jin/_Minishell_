/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:34 by djin              #+#    #+#             */
/*   Updated: 2024/08/04 16:54:46 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_print(void *cmd)
{
	printf("%s", (char *)cmd);
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
	start_parse(ast, tokens, envp);
	while ((*ast)->parent != NULL)
		(*ast) = (*ast)->parent;
	if (!execute_dollar(ast, 0, envp))
	{
		printf("Error: dollar expansion failed\n");
		return ;
	}
	(*ast) = minishell;
	minishell = (*ast);
	exec = executing(ast, exec);
	exec = renamed_here_doc(exec);
	if (ft_strcmp(exec->cmd[0], "<<") > 0)
		execute(exec, envp);
	free_exec(exec);
	(*ast) = minishell;
	traverse(ast, free, 0, false);
	free(ast);
}