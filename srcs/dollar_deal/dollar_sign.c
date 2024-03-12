/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 03:28:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast *ast, bool create_sibling, char **envp)
{
	char	*strtrim;
	char	*tmp;

	create_sibling = false;
	strtrim = init_dollar(ast);
	if (strtrim == NULL)
		return;
	build_dollar(strtrim, ast, create_sibling, envp);
}