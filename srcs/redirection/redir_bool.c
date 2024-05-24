/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:45 by geibo             #+#    #+#             */
/*   Updated: 2024/05/24 15:40:21 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(char *cmd)
{
	return (ft_strcmp(cmd, ">") == 0
		|| ft_strcmp(cmd, "<<") == 0
		|| ft_strcmp(cmd, "<") == 0);
}

bool	is_redir_in(char *cmd)
{
	return (ft_strcmp(cmd, "<") == 0);
}

bool	is_redir_out(char *cmd)
{
	return (ft_strcmp(cmd, ">") == 0);
}

bool	is_redir_append(char *cmd)
{
	return (ft_strcmp(cmd, ">>") == 0);
}
