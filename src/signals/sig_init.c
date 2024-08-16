/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 15:40:46 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(t_mshell *msh)
{
	struct sigaction	ms_sigs;

	ms_sigs.sa_sigaction = ms_sighandle;
	ms_sigs.sa_flags = SA_SIGINFO;
	sigaction (SIGINT, &ms_sigs, NULL);
	sigaction (SIGQUIT, &ms_sigs, NULL);
	(void)msh;
}
