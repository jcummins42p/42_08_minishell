/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 14:39:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	echo_env(char *env[])
{
	int i;
	i = 0;
	while(env[i])
		printf("%s\n", env[i++]);
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argv;
	(void)argc;
	char 		*ptr;
	t_tokenlist *tokens;
	t_envlist	*envlist;

	tokens = NULL;
	envlist = NULL;
	env_init(&envlist, env);
	/*env_print(&envlist);*/
	while (1)
	{
		ptr = readline("Enter text: ");
		add_history(ptr);
		tokenize(&tokens, ptr);
		token_clear(&tokens);
		printf("%s\n", ptr);
		if (!strncmp(ptr, "EXIT", 4))
		{
			free(ptr);
			break ;
		}
		if (!strncmp(ptr, "PRINT", 4))
		{
			printf("%s\n", ptr);
			free(ptr);
			break ;
		}
		if (!strncmp(ptr, "env", 3))
			echo_env(env);
		free(ptr);
		ptr = NULL;
	}
	return (0);
}
