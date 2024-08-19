/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 15:52:07 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(t_mshell *msh)
{
	sigset_t			sigset;

	ft_memset(&msh->ms_sigs, 0, sizeof(struct sigaction));
	ft_memset(&msh->ms_ignr, 0, sizeof(struct sigaction));
	msh->ms_sigs.sa_sigaction = ms_sighandle;
	msh->ms_ignr.sa_sigaction = ms_sigignore;
	msh->ms_sigs.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	msh->ms_ignr.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigemptyset(&msh->ms_sigs.sa_mask);
	sigemptyset(&msh->ms_ignr.sa_mask);
	sigaction (SIGINT, &msh->ms_sigs, NULL);
	sigaction (SIGQUIT, &msh->ms_ignr, NULL);
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &sigset, NULL) != 0)
		perror("sigprocmask");
	(void)msh;
}
