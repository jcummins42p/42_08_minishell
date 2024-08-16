/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:15:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 17:10:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

//	sig_init.c
void	sig_init(t_mshell *msh);

//	sig_handlers.c
void	ms_sighandle(int sig, siginfo_t *info, void *ucontext);

#endif
