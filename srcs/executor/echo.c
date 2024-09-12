/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:56:56 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/12 16:57:59 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_echo(char **args)
{
	int		i;
	bool	n_flag;

	// printf("Executing cd...\n");
	i = 1;
	if (args && args[1])
	{
		if (ft_strncmp(args[1], "-n", 2) == 0)
		{
			n_flag = true;
			i++;
		}
		while (args[i + 1] != NULL)
			printf("%s ", args[i++]);
		printf("%s", args[i++]);
	}
	if (n_flag == false)
		printf("\n");
	return (true);
}
