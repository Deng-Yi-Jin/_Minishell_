/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_unfinished_q.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:13:07 by kytan             #+#    #+#             */
/*   Updated: 2024/09/16 16:19:59 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_unfinished_q(char *input, char q)
{
	char	*buffer;

	if (!q || !input)
		return (0);
	buffer = ft_calloc(1, sizeof(char));
	while (!ft_strchr(buffer, q))
	{
		free(buffer);
		buffer = readline(" > ");
		if (!input)
			break ;
		input = ft_strfjoin(input, "\n");
		input = ft_strfjoin(input, buffer);
	}
	free(buffer);
	return (input);
}
