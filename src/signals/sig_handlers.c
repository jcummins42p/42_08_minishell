/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 16:02:25 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sighandle(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;

	if (sig == SIGINT)
		g_siginfo = SIGINT;
	else if (sig == SIGQUIT)
		g_siginfo = SIGQUIT;
}
