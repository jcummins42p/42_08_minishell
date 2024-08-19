/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 14:02:14 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(t_mshell *msh)
{
	struct sigaction	ms_sigs;

	ft_memset(&ms_sigs, 0, sizeof(struct sigaction));
	ms_sigs.sa_sigaction = ms_sighandle;
	ms_sigs.sa_flags = SA_SIGINFO;
	sigemptyset(&ms_sigs.sa_mask);
	sigaction (SIGINT, &ms_sigs, NULL);
	sigaction (SIGQUIT, &ms_sigs, NULL);
	(void)msh;
}
