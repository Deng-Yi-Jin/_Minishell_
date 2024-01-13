/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/01/13 06:43:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast **ast)
{
	char	*strtrim;
	int		i;
	int		count_words;
	int		j;

	count_words = 0;
	i = 0;
	while ((*ast)->type != DOLLAR)
		(*ast) = (*ast)->next_grandchild;
	strtrim = ft_strtrim((*ast)->cmd, "$(");
	j = ft_strlen(strtrim);
	j = j - 1;
	if (strtrim[j] == ')')
		strtrim[j] = '\0';
	printf("%s\n", strtrim);
	printf("%s\n", (*ast)->cmd);
	free(strtrim);
}