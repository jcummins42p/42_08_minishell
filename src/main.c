/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/21 16:32:54 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_siginfo = 0;

int	main(int argc, char *argv[], char *env[])
{
	t_mshell	msh;

	(void)argv;
	(void)argc;
	shell_init(&msh);
	sig_init(&msh);
	env_init(&msh.envlist, env);
	env_set_string(&msh.envlist, &msh.env);
	shell_set_envptrs(&msh);
	input_cycle(&msh);
	shell_free(&msh);
	if (msh.exitcode > EX_MAX_ERR)
		msh.exitcode = EX_MAX_ERR;
	return (msh.exitcode);
}
