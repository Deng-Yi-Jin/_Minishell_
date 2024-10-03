/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:38:12 by geibo             #+#    #+#             */
/*   Updated: 2024/10/02 15:25:20 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(t_exec *exec, int *i)
{
	int	cmd_line;

	cmd_line = count_cmd_line(exec, 0);
	allocate_cmd_list(exec, cmd_line);
	copy_cmd_to_list(exec);
}

int	count_redir(t_exec *exec, int i)
{
	int	redir_line;

	redir_line = 0;
	while (exec->cmd[i] != NULL)
	{
		if (is_redir_in(exec->cmd[i]))
			redir_line++;
		else if (is_redir_out(exec->cmd[i]))
			redir_line += 2;
		i++;
	}
	return (redir_line);
}

void	allocate_redir_list(t_exec *exec, int redir_line)
{
	if (redir_line + 1 > SIZE_MAX / sizeof(char *))
	{
		fprintf(stderr, "Error: Allocation size too large\n");
		exit(EXIT_FAILURE);
	}
	exec->redir_list = ft_calloc(redir_line + 2, sizeof(char *));
	if (exec->redir_list == NULL)
	{
		perror("ft_calloc");
		exit(EXIT_FAILURE);
	}
}

void	copy_redir_to_list(t_exec *exec)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (exec->cmd[word])
	{
		if (is_redir_in(exec->cmd[word]))
		{
			exec->redir_list[i] = ft_strdup(exec->cmd[word]);
			printf("%s\n", exec->redir_list[i]);
			i++;
		}
		else if (is_redir_out(exec->cmd[word]))
		{
			exec->redir_list[i++] = ft_strdup(exec->cmd[word++]);
			exec->redir_list[i] = ft_strdup(exec->cmd[word]);
			i++;
		}
		word++;
	}
}

void	process_redirection(t_exec *exec, int *i)
{
	int	redir_line;

	redir_line = count_redir(exec, 0);
	allocate_redir_list(exec, redir_line);
	copy_redir_to_list(exec);
}
