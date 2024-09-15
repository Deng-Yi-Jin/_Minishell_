/* ************************************************************************** */
/*		*/
/*		:::			::::::::	 */
/*	 env.c			:+:			:+:		:+:	 */
/*		+:+ +:+		 +:+		 */
/*	 By: kytan <kytan@student.42kl.edu.my>			+#+	+:+			 +#+		*/
/*		+#+#+#+#+#+	 +#+			 */
/*	 Created: 2024/09/06 12:53:53 by kytan		 #+#		#+#		 */
/*	 Updated: 2024/09/07 18:35:46 by kytan		###	 ########.fr			 */
/*		*/
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(char **args)
{
	int i;

	if (!args || args[1])
		return (false);
	i = 0;
	while (g_main->env_vars[i]->key != NULL)
	{
		printf("%s=%s\n", g_main->env_vars[i]->key, g_main->env_vars[i]->value);
		i++;
	}
}