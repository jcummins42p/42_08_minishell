/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 17:33:54 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sighandle(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;

	if (sig == SIGINT)
	{
		// Write the ^C indication to the terminal
		// Clear the current line in readline
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// Optionally display ^C and a new prompt
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
