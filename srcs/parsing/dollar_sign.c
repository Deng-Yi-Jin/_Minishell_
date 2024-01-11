/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/01/11 13:35:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast **ast)
{
	char	*strtrim;
	int		i;
	int		count_words;

	count_words = 0;
	i = 0;
	while ((*ast)->type != DOLLAR)
		(*ast) = (*ast)->next_grandchild;
	if ((*ast)->type == DOLLAR)
		strtrim = ft_strtrim((*ast)->cmd, "$()");
	while (strtrim[i])
	{
		if (strtrim[i] == ' ' || strtrim[i] == '\t')
			i++;
		else if ((strtrim[i] !=  ' ' && strtrim[i] != '\t') && strtrim[i])
		{
			while (strtrim[i] != ' '  && strtrim[i] != '\t' && strtrim[i])
			{
				i++;
				count_words++;
			}
			
		}
	}
	printf("%s\n", strtrim);
	printf("%s\n", (*ast)->cmd);
	free(strtrim);
}