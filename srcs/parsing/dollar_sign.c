/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/01/20 04:11:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast *ast)
{
	char	*strtrim;
	char	*tmp;
	int		strlen;
	int		i;
	int		count_words;
	int		j;

	count_words = 0;
	i = 0;
	strtrim = "";
	if ((ast)->type != DOLLAR)
		return;
	if ((ast)->cmd[i] == '$')
		strtrim = ft_strtrim((ast)->cmd, "$");
	strlen = ft_strlen(strtrim) - 1;
	if (ft_bracket(strtrim[strlen]) == true)
		strtrim[strlen] = '\0';
	while (strtrim[i] != '\0')
	{
		if (ft_bracket(strtrim[i]) == true)
			i++;
		if (strtrim[i] == ' ')
			i++;
		j = i;
		if (strtrim[i] == '$')
		{
			j = i;
			i++;
			count_words++;
			if (strtrim[i] == '(')
				quoting(strtrim, &i, &count_words, ')');
			else if (strtrim[i] == '{')
				quoting(strtrim, &i, &count_words, '}');
			else if (strtrim[i] == '\"')
				quoting(strtrim, &i, &count_words, '\"');
			else if (strtrim[i] == '\'')
				quoting(strtrim, &i, &count_words, '\'');
			else if (strtrim[i] == '[')	
				quoting(strtrim, &i, &count_words, ']');
			else
			{
				while (ft_symbol(strtrim[i]) == false && strtrim[i])
				{
					i++;
					count_words++;
				}
			}
		}
		else
		{
			while (ft_symbol(strtrim[i]) == false && strtrim[i])
			{
				i++;
				count_words++;
			}
		}
		if (strtrim[i] == '\0')
			break;
		// ast->next_grandchild = create_ast_node(ft_substr(strtrim, j, count_words), 0);
		// ast->next_grandchild->prev_grandchild = ast;
		// ast = ast->next_grandchild;
		printf("ast->cmd: %s\n", ast->cmd);
	}
	free(strtrim);
}