/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:50:07 by geibo             #+#    #+#             */
/*   Updated: 2024/09/30 13:46:41 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_content(int fd, char *limiter)
{
	char	*input;

	input = readline("> ");
	while (1)
	{
		if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
}

t_exec	*copy_nodes(t_exec *exec)
{
	t_exec	*another;
	t_exec	*temp;
	t_exec	*head;
	int		len;
	int		i;

	another = NULL;
	temp = exec;
	head = 0;
	while (temp)
	{
		i = 0;
		len = ft_sstrlen(temp->cmd);
		another = join_exec_nodes(another, ft_calloc(len + 1, sizeof(char *)),
				ft_calloc(len + 1, sizeof(int)));
		if (!head)
			head = another;
		copy_n_paste(another->cmd, temp->cmd, &i);
		temp = temp->next;
	}
	another = head;
	return (another);
}

void	create_here_doc_file(char *str, char *limiter)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	read_content(fd, limiter);
	close(fd);
}

void	open_here_doc_file(t_exec *temp, int *i)
{
	char	*str;
	char	*limiter;
	char	*tmp1;
	int		count;

	count = 0;
	while (temp->cmd[*i])
	{
		if (ft_strcmp(temp->cmd[*i], "<<") == 0)
		{
			str = ft_itoa(count++);
			(*i)++;
			limiter = ft_strdup(temp->cmd[*i]);
			free(temp->cmd[*i]);
			temp->cmd[*i] = ft_strjoin(ft_strdup("test_"), str);
			free(str);
			str = ft_strjoin(temp->cmd[*i], ".txt");
			temp->cmd[*i] = str;
			create_here_doc_file(temp->cmd[*i], limiter);
			free(limiter);
			(*i)++;
		}
		else
			handle_not_heredoc(tmp1, temp, i);
	}
}

t_exec	*renamed_here_doc(t_exec *exec, char **envp)
{
	t_exec	*another;
	t_exec	*temp;
	int		i;

	another = copy_nodes(exec);
	temp = another;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			open_here_doc_file(temp, &i);
		}
		temp = temp->next;
	}
	free_exec(exec);
	exec = another;
	set_exec_type(exec, envp);
	return (exec);
}
