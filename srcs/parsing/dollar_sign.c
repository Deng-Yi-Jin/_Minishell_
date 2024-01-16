/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/01/16 08:20:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast *ast)
{
	char	*strtrim;
	int		i;
	int		count_words;
	int		j;

	count_words = 0;
	i = 0;
	if ((ast)->type != DOLLAR)
		return;
	while ((ast)->cmd[i] != '\0')
	{
		if ((ast)->cmd[i] == '$')
		{
			i++;
			
		}
		
	}
	printf("%s\n", strtrim);
	printf("%s\n", (ast)->cmd);
	free(strtrim);
}