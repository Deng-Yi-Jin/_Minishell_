/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:34:55 by geibo             #+#    #+#             */
/*   Updated: 2024/03/12 03:28:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_dollar(t_ast *ast)
{
	t_count	count;
	char	*strtrim;

	count = (t_count){0,0,0,0};
	if ((ast)->cmd[0] != '$' || (ast)->type != DOLLAR)
		return (NULL);
	if ((ast)->cmd[count.i] == '$')
		strtrim = ft_strtrim((ast)->cmd, "$");
	count.strlen = ft_strlen(strtrim) - 1;
	while (strtrim[count.strlen] == ' ' || strtrim[count.strlen] == '\t')
		strtrim[count.strlen--] = '\0';
	if (ft_bracket(strtrim[count.strlen]) == true)
		strtrim[count.strlen] = '\0';
	return (strtrim);
}

void	trim_new_str(char *strtrim, int *i, int *j, int *count_words)
{
	*count_words = 0;
	if (ft_bracket(strtrim[*i]) == true)
		(*i)++;
	while (strtrim[*i] == ' ' || strtrim[*i] == '\t')
		(*i)++;
	*j = *i;
	if (strtrim[*i] == '$')
		dollar(strtrim, i, count_words);
	else
	{
		while (strtrim[*i] != '$' && ft_symbol(strtrim[*i]) == false && strtrim[*i])
		{
			if (strtrim[*i] == '\"')
				quoting(strtrim, i, count_words, '\"');
			else if (strtrim[*i] == '\'')
				quoting(strtrim, i, count_words, '\'');
			else
			{
				(*i)++;
				(*count_words)++;
			}
		}
	}
	while (strtrim[*i] == ' ')
		(*i)++;
}

t_ast	*add_older_dollar(t_ast *ast, char *strtrim, int *j, int *count_words)
{
	ast->child = create_ast_node(ft_substr(strtrim, *j, *count_words), 0);
	ast->child->parent = ast;
	ast = ast->child;
	if (strtrim[*j] == '\"' || strtrim[*j] == '\'')
		ast->type = QUOTE;
	else if (strtrim[*j] == '$')
		ast->type = DOLLAR;
	else
		ast->type = WORD;
	return (ast);
}

t_ast	*add_sibling_dollar(t_ast *ast, char *strtrim, int *j, int *count_words)
{
	ast->next = create_ast_node(ft_substr(strtrim, *j, *count_words), 0);
	ast->next->parent = ast->parent;
	ast->next->prev = ast;
	ast = ast->next;
	if (strtrim[*j] == '\"' || strtrim[*j] == '\'')
		ast->type = QUOTE;
	else if (strtrim[*j] == '$')
		ast->type = DOLLAR;
	else
		ast->type = WORD;
	return (ast);
}

void	build_dollar(char *strtrim, t_ast *ast, bool create_sibling, char **envp)
{
	t_count	count;

	count = (t_count) {0,0,0,0};
	while (strtrim[count.i] != '\0')
	{
		trim_new_str(strtrim, &count.i, &count.j, &count.count_words);
		if (create_sibling == false)
		{
			ast = add_older_dollar(ast, strtrim, &count.j, &count.count_words);
			create_sibling = true;
		}
		else if (create_sibling == true)
			ast = add_sibling_dollar(ast, strtrim, &count.j, &count.count_words);
	}
	free(strtrim);
	create_sibling = false;
	if (ast->cmd[0] == '$')
	{
		(ast)->type = DOLLAR;
		dollar_deal(ast, create_sibling);
	}
	else
		(ast)->type = is_command((ast)->cmd, envp);
}
