/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:50:07 by geibo             #+#    #+#             */
/*   Updated: 2024/06/13 19:09:39 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sstrlen(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
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
		another = join_exec_nodes(another, ft_calloc(len + 1, sizeof(char *)));
		if (!head)
			head = another;
		while (temp->cmd[i])
		{
			another->cmd[i] = ft_strdup(temp->cmd[i]);
			i++;
		}
		temp = temp->next;
	}
	another = head;
	return (another);
}

void	create_here_doc_file(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	close(fd);
}

void	open_here_doc_file(t_exec *temp, int *i)
{
	char	*str;
	int		count;

	count = 0;
	while (temp->cmd[*i])
	{
		if (ft_strcmp(temp->cmd[*i], "<<") == 0)
		{
			str = ft_itoa(count);
			count++;
			(*i)++;
			free(temp->cmd[*i]);
			temp->cmd[*i] = ft_strjoin(ft_strdup("test_"), str);	
			free(str);
			str = ft_strjoin(ft_strdup(temp->cmd[*i]), ".txt");
			free(temp->cmd[*i]);
			temp->cmd[*i] = str;
			create_here_doc_file(temp->cmd[*i]);
		}
		else
		{
			temp->cmd[*i] = ft_strdup(temp->cmd[*i]);
			(*i)++;
		}
	}
}

// void	here_doc_file()

t_exec	*renamed_here_doc(t_exec *exec)
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
			open_here_doc_file(temp, &i);
		temp = temp->next;
	}
	free_exec(exec);
	exec = another;
	while (exec)
	{
		print_exec(exec);
		exec = exec->next;
	}
	exec = another;
	return (exec);
}
