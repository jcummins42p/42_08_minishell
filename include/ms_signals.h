/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:15:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 15:41:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

//	sig_init.c
void	sig_init(t_mshell *msh);

//	sig_handlers.c
void	ms_sighandle(int sig, siginfo_t *info, void *ucontext);
void	ms_sigignore(int sig, siginfo_t *info, void *ucontext);

#endif
