/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:56:56 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/06 17:55:14 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_echo(char **args, char **flags)
{
	int		i;
	bool	trailing;

	i = 0;
	trailing = true;
	if (ft_strcmp(flags[0], "-n") == 0)
	{
    trailing = false;
    i++;
  }
	i = 1;
	while (args[i] != NULL)
  {
    printf("%s ", args[i++]);
  }
  printf("%s", args[i]);
	if (trailing == true)
		printf("\n");
	return (true);
}

/*
bool	execute_echo(char **args, char **flags)
{
	int		i;
	bool	trailing;

	trailing = true;
  printf("Executing echo...\n");
	if (!args || !args[0])
	i = 1;
	if (ft_strncmp(args[1], "-n", 2) == 0)
	{
		trailing = false;
		i++;
	}
	while (args[i + 1] != NULL)
		printf("%s ", args[i++]);
	printf("%s", args[i]);
	if (trailing == true)
		printf("\n");
	return (true);
}*/