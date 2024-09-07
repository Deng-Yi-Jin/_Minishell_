/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:18:19 by codespace         #+#    #+#             */
/*   Updated: 2024/09/07 15:42:58 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_color(char *str)
{
	char	msg[1024];

	ft_snprintf(msg, sizeof(msg), "%s%s%s", RED, str, CYAN);
	perror(msg);
	printf("%s", RESET_COLOR);
}

void	error_exit(char *str, bool is_perror)
{
	char	*msg;

	msg = malloc(1024);
	ft_snprintf(msg, 1024, "%s%s%s", RED, str, RESET_COLOR);
	if (is_perror)
		perror(msg);
	else
		printf("%s", msg);
	free(msg);
	exit(errno);
}

void  print_my_env_vars(void)
{
  int i = 0;
  printf("\nIM PRINTING TO CHECK THE LIST BEFORE EXIT WHY IS THERE NO HI=HELLO?\n\n");
  while (g_main->env_vars[i]->key != NULL)
  {
    printf("g_main->env_vars[i]->key = [%s]\n", g_main->env_vars[i]->key);
    printf("g_main->env_vars[i]->value = [%s]\n", g_main->env_vars[i]->value);
    i++;
  }
}

void	exit_success(void)
{
	printf("%sBELLA CIAO%s\n", BLUE_BOLD, RESET_COLOR);
	free_env_vars();
	exit(EXIT_SUCCESS);
}

void	free_jutsu(bool darr, char *key, char *value)
{
	if (darr == true)
		free_darr(g_main->envp);
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
}
