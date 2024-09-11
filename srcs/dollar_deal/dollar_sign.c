/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/09/10 13:36:59 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_isunclosed_q(char *s)
{
	char	q;

	q = 0;
	while (*s)
	{
		if (*s == q)
			q = 0;
		else if (*s == '\"' || *s == '\'')
			q = *s;
		s++;
	}
	return (q);
}

void	dollar_deal(t_ast *ast, bool create_sibling, char **envp)
{
	char	*strtrim;

	create_sibling = false;
	strtrim = init_dollar(ast); //redo this function
	if (strtrim == NULL)
		return ;
	// if (strtrim[0] != '(')
	// {
	// 	strtrim = env_expansion(ft_split(strtrim, ' '), ft_isunclosed_q(strtrim));
	// 	printf("output = [%s]", strtrim);
	// }
	// else
		// build_dollar(strtrim, ast, create_sibling, envp);
}
