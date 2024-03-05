/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:06:59 by geibo             #+#    #+#             */
/*   Updated: 2024/03/05 19:11:22 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	traverse(t_ast **ast, void (*f)(void *), int depth, bool print)
{
	t_ast	*temp;

	if (*ast == NULL)
		return (false);
	temp = (*ast)->next;
	if (print == false && (*ast)->cmd != NULL)
	{
		printf("%s\n", (*ast)->cmd);
	}
	traverse(&((*ast)->child), f, depth + 1, print);
	f((*ast)->cmd);
	f((*ast));
	traverse(&temp, f, depth, print);
	return (true);
}
