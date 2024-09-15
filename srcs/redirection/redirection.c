/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:17:49 by geibo             #+#    #+#             */
/*   Updated: 2024/09/15 18:03:02 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_exec *exec, int *infilefd, int *outfilefd)
{
	int	i;
	int	count;
	int	j;
	int	cmd_line;

	i = 0;
	while (exec->cmd[i])
	{
		if (is_redir(exec->cmd[i]))
		{
			exec->redir_list = ft_calloc(3, sizeof(char *));
			exec->redir_list[0] = ft_strdup(exec->cmd[i]);
			exec->redir_list[1] = ft_strdup(exec->cmd[i + 1]);
			exec->redir_list[2] = NULL;
			i += 2;
		}
		else
		{
			j = i;
            cmd_line = 0; // Initialize cmd_line to 0 before counting
            while (exec->cmd[i] != NULL && !is_redir(exec->cmd[i]))
            {
                cmd_line++;
                i++;
            }
            // Check for potential overflow before allocation
            if (cmd_line + 1 > SIZE_MAX / sizeof(char *))
            {
                printf(stderr, "Error: Allocation size too large\n");
                exit(EXIT_FAILURE);
            }
            exec->cmd_list = ft_calloc(cmd_line + 1, sizeof(char *));
            if (exec->cmd_list == NULL)
            {
                perror("ft_calloc");
                exit(EXIT_FAILURE);
            }
            cmd_line = 0;
            while (j < i)
            {
                exec->cmd_list[cmd_line] = ft_strdup(exec->cmd[j]);
                if (exec->cmd_list[cmd_line] == NULL)
                {
                    perror("ft_strdup");
                    exit(EXIT_FAILURE);
                }
                cmd_line++;
                j++;
            }
            exec->cmd_list[cmd_line] = NULL;
		}
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
