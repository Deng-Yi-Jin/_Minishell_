/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:38:12 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 14:38:41 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(t_exec *exec, int *i)
{
	int	cmd_line;

	cmd_line = count_cmd_line(exec, *i);
	allocate_cmd_list(exec, cmd_line);
	copy_cmd_to_list(exec, i, cmd_line);
}

void	process_redirection(t_exec *exec, int *i)
{
	exec->redir_list = ft_calloc(3, sizeof(char *));
	exec->redir_list[0] = ft_strdup(exec->cmd[*i]);
	exec->redir_list[1] = ft_strdup(exec->cmd[*i + 1]);
	exec->redir_list[2] = NULL;
	*i += 2;
}
