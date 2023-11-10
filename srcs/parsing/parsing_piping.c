/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:34:26 by root              #+#    #+#             */
/*   Updated: 2023/09/25 20:02:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ast_strjoin(t_token **tokens, char *str)
{
	if ((*tokens)->type == MINUS && (*tokens)->next->type == WORD)
	{
		str = ft_strjoin((*tokens)->cmd, (*tokens)->next->cmd);
		*tokens = (*tokens)->next->next;
	}
	else if ((*tokens)->type == WORD)
	{
		str = ft_strdup((*tokens)->cmd);
		(*tokens) = (*tokens)->next;
	}
	return	(str);
}
