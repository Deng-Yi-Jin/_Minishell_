/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:17:49 by geibo             #+#    #+#             */
/*   Updated: 2024/10/03 23:40:38 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd_line(t_exec *exec, int i)
{
	int	cmd_line;

	cmd_line = 0;
	while (exec->cmd[i] != NULL)
	{
		if (is_redir(exec->cmd[i]))
			break ;
		if (!is_redir(exec->cmd[i]))
			cmd_line++;
		i++;
	}
	return (cmd_line);
}

void	allocate_cmd_list(t_exec *exec, int cmd_line)
{
	if (cmd_line + 1 > SIZE_MAX / sizeof(char *))
	{
		fprintf(stderr, "Error: Allocation size too large\n");
		exit(EXIT_FAILURE);
	}
	exec->cmd_list = ft_calloc(cmd_line + 1, sizeof(char *));
	if (exec->cmd_list == NULL)
	{
		perror("ft_calloc");
		exit(EXIT_FAILURE);
	}
}

void	copy_cmd_to_list(t_exec *exec)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (exec->cmd[word])
	{
		if (is_redir(exec->cmd[word]))
			break ;
		if (!is_redir(exec->cmd[word]))
		{
			exec->cmd_list[i] = ft_strdup(exec->cmd[word]);
			i++;
		}
		word++;
	}
}

void	redirect(t_exec *exec, int *infilefd, int *outfilefd)
{
	int	i;

	i = 0;
	while (exec->cmd[i])
	{
		if (is_redir(exec->cmd[i]))
		{
			process_redirection(exec, 0);
			break ;
		}
		i++;
	}
	process_command(exec, 0);
}

int	return_after_redir(t_exec *exec, int i)
{
	while (exec->cmd_list[i] != NULL)
	{
		if (is_redir_in(exec->cmd_list[i]))
			i += 2;
		else
			break ;
	}
	return (i);
}
