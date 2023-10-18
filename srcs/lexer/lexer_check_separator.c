/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:27:44 by codespace         #+#    #+#             */
/*   Updated: 2023/10/18 17:24:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_symbol(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (true);
	return (false);
}

int ft_return_op(char input)
{
	if (input == '>')
		return (REDIR_OUT);
	else if (input == '<')
		return (REDIR_IN);
	else if (input == '|')
		return (PIPE);
	else if (input == ' ')
		return (SPACE);
	return (0);
}