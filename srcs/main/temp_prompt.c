/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 02:29:43 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 13:47:57 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


char *quotes_author(void)
{
    char *quotes[] = {
        "Socrates",
        "Socrates",
        "René Descartes",
        "Wittgenstein",
        "Nelson Mandela",
        "Emerson",
        "Confucius",
        "Confucius",
        "Plato",
        "Heraclitus",
        "sinlee",
        "sinlee"
    };
    return (quotes[ft_atoi(find_env_vars("NUM_QUOTES")->value) % (sizeof(quotes) / sizeof(quotes[0]))]);
}

char *pick_quotes(void)
{
    char *quotes[] = {
        "The only true wisdom is in knowing you know nothing.",
        "The unexamined life is not worth living.",
        "I think, therefore I am.",
        "Whereof one cannot speak, thereof one must be silent.",
        "The greatest glory in living lies not in never falling, but in rising every time we fall.",
        "To be yourself in a world that is constantly trying to make you something else is the greatest accomplishment.",
        "The only way to deal with life's imperfections is to enjoy each and every day.",
        "Life is really simple, but we insist on making it complicated.",
        "The unexamined life is not worth living.",
        "Our lives are like a candle in the wind.",
    };
    return (quotes[ft_atoi(find_env_vars("NUM_QUOTES")->value) % (sizeof(quotes) / sizeof(quotes[0]))]);
}

static void prompt_quotes(char	prompt[LOGIN_NAME_MAX + PATH_MAX + 20])
{
    char	cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    ft_snprintf(prompt, (LOGIN_NAME_MAX + PATH_MAX + 20), "\033[0;35m@%s %s-> %s%s%s $ %s",
            quotes_author(), RESET_COLOR, BLUE_BOLD, pick_quotes(), RESET_COLOR, CYAN);
    modify_env_vars("NUM_QUOTES", ft_itoa(ft_atoi(find_env_vars("NUM_QUOTES")->value) + 1));
}

char *prompt_msg(char	prompt[LOGIN_NAME_MAX + PATH_MAX + 20])
{
    char	*username;
    char	cwd[PATH_MAX];
    
    username = getenv("USER");
    if (username == NULL)
    {
        perror("getenv");
        exit(EXIT_FAILURE);
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    // printf("QUOTES: %s", find_env_vars("QUOTES").value);
    if (!ft_strcmp(find_env_vars("QUOTES")->value, "1"))
        prompt_quotes(prompt);
    else
        ft_snprintf(prompt, (LOGIN_NAME_MAX + PATH_MAX + 20), "\033[0;35m@%s %s-> %s%s%s $ %s",
            username, RESET_COLOR, BLUE_BOLD, cwd, RESET_COLOR, CYAN);
    return (prompt);
}