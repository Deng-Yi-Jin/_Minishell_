/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/01/10 14:25:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast **ast)
{
	int		dollar;
	int		open_brack;
	int		close_brack;
	int		i;
	int		strlen;
	char	*strtrim;

	dollar = 0;
	open_brack = 0;
	close_brack = 0;
	i = 0;
	(*ast) = ast_first_last((*ast), true, false);
	while ((*ast)->type != DOLLAR)
		(*ast) = (*ast)->next_grandchild;
	while ((*ast)->cmd[i])
	{
		if ((*ast)->cmd[i] == '$')
			dollar++;
		else if ((*ast)->cmd[i] == '(')
			open_brack++;
		else if ((*ast)->cmd[i] == ')')
			close_brack++;
		i++;
	}
	if (dollar > 0 && open_brack > 0 && close_brack > 0)
	{
		strlen = ft_strlen((*ast)->cmd) - dollar - open_brack - close_brack;
		strtrim = malloc(sizeof(char) * strlen);
		
	}
	free(strtrim);
	printf("%d\n%d\n%d\n%d\n", dollar, open_brack, close_brack, strlen);
	printf("%s\n", (*ast)->cmd);
}