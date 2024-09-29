/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:17:49 by geibo             #+#    #+#             */
/*   Updated: 2024/09/29 17:13:46 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd_line(t_exec *exec, int i)
{
	int	cmd_line;

	cmd_line = 0;
	while (exec->cmd[i] != NULL && !is_redir(exec->cmd[i]))
	{
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

void	copy_cmd_to_list(t_exec *exec, int *i, int cmd_line)
{
	int	j;
	int	k;

	j = *i;
	k = 0;
	// printf("CMD_LINE IN COPY_CMD_TO_LIST = %i\n", cmd_line);
	while (k < cmd_line)
	{
		exec->cmd_list[k] = ft_strdup(exec->cmd[j]);
		if (exec->cmd_list[k] == NULL)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		k++;
		j++;
	}
	exec->cmd_list[k] = NULL;
	*i = j;
}

void	redirect(t_exec *exec, int *infilefd, int *outfilefd)
{
	int	i;

	i = 0;
	// printf("REDIRECTION HAPPENS HERE\n");
	while (exec->cmd[i])
	{
		if (is_redir(exec->cmd[i]))
			process_redirection(exec, &i);
		else
			process_command(exec, &i);
	}
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
