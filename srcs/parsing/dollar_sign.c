/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/03/05 15:20:00 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast *ast, bool create_sibling)
{
	char	*strtrim;
	char	*tmp;
	int		strlen;
	int		i;
	int		count_words;
	int		j;

	if ((ast)->cmd[0] != '$')
		return;
	create_sibling = false;
	i = 0;
	strtrim = "";
	if ((ast)->type != DOLLAR)
		return;
	if ((ast)->cmd[i] == '$')
		strtrim = ft_strtrim((ast)->cmd, "$");
	strlen = ft_strlen(strtrim) - 1;
	//printf("strtrim = %s\n", strtrim);
	while (strtrim[strlen] == ' ' || strtrim[strlen] == '\t')
	{
		strtrim[strlen] = '\0';
		strlen--;
	}
	if (ft_bracket(strtrim[strlen]) == true)
		strtrim[strlen] = '\0';
	while (strtrim[i] != '\0')
	{
		count_words = 0;
		if (ft_bracket(strtrim[i]) == true)
			i++;
		while(strtrim[i] == ' ' || strtrim[i] == '\t')
			i++;
		j = i;
		if (strtrim[i] == '$')
			dollar(strtrim, &i, &count_words);
		else
		{
			while (strtrim[i] != '$' && ft_symbol(strtrim[i]) == false && strtrim[i] != '\0')
			{
				if (strtrim[i] == '\"')
					quoting(strtrim, &i, &count_words, '\"');
				else if (strtrim[i] == '\'')
					quoting(strtrim, &i, &count_words, '\'');
				else if (strtrim[i] == '`')
					quoting(strtrim, &i, &count_words, '`');
				else
				{
					i++;
					count_words++;
				}
			}
		}
		while (strtrim[i] == ' ')
			i++;
		if (create_sibling == false)
		{
			(ast)->child = create_ast_node(ft_substr(strtrim, j, count_words), 0);
			(ast)->child->parent = (ast);
			(ast) = (ast)->child;
			create_sibling = true;
			if (strtrim[j] == '\"' || strtrim[j] == '\'' || strtrim[j] == '`')
				(ast)->type = QUOTE;
			else if (strtrim[j] == '$')
				(ast)->type = DOLLAR;
			else
				(ast)->type = WORD;
		}
		else if (create_sibling == true)
		{
			(ast)->next = create_ast_node(ft_substr(strtrim, j, count_words), 0);
			(ast)->next->parent = (ast)->parent;
			(ast)->next->prev = (ast);
			(ast) = (ast)->next;
			if (strtrim[j] == '\"' || strtrim[j] == '\'' || strtrim[j] == '`')
				(ast)->type = QUOTE;
			else if (strtrim[j] == '$' && strtrim[j + 1] == '(')
				(ast)->type = CMD_EXPANSION;
			else if (strtrim[j] == '$')
				(ast)->type = DOLLAR;
			else
				(ast)->type = WORD;
		}
		// printf("ast->type = %d\n", (ast)->type);
	}
	create_sibling = false;
	// printf("ast->cmd[0] = %c\n", ast->cmd[0]);
	if (ast->cmd[0] == '$')
	{
		(ast)->type = DOLLAR;
		dollar_deal(ast, create_sibling);
	}
	//printf("strtrim = %s\n", strtrim);
	free(strtrim);
}