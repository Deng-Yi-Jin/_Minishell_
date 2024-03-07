/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:10:17 by codespace         #+#    #+#             */
/*   Updated: 2024/03/07 18:33:02 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_deal(t_ast *ast, bool create_sibling)
{
	char	*strtrim;
	char	*tmp;
 
	// count = (t_count){0,0,0,0};
	create_sibling = false;
	strtrim = init_dollar(ast);
	if (strtrim == NULL)
		return;
	build_dollar(strtrim, ast, create_sibling);
}