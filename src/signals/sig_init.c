/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 17:33:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(t_mshell *msh)
{
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&msh->ms_sigs, 0, sizeof(struct sigaction));
	msh->ms_sigs.sa_sigaction = ms_sighandle;
	msh->ms_sigs.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	sigemptyset(&msh->ms_sigs.sa_mask);
	sigaction (SIGINT, &msh->ms_sigs, NULL);
}
