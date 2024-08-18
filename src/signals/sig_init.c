/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/18 15:27:35 by akretov          ###   ########.fr       */
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
