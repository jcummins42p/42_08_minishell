/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:41:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/15 19:34:26 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

//	com_cd.c
void		com_cd(t_mshell *msh, t_tokenlist *token);

//	com_echo.c
bool		is_redirect(t_tokenlist *token);
void		com_echo(t_mshell *msh, t_tokenlist *token);

//	com_env.c
void		com_env(t_envlist **envlist, t_vscope scope);

//	com_exit.c
void		com_exit(t_mshell *msh, t_tokenlist *token);

//	com_export.c
void		com_export(t_mshell *msh, t_tokenlist *token, t_vscope scope);

//	com_unset.c
void		com_unset(t_mshell *msh);

#endif
