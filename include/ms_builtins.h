/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:41:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/13 15:08:54 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

//	com_cd.c
void		change_dir(t_mshell *msh, t_tokenlist *token);

//	com_echo.c
bool		is_redirect(t_tokenlist *token);
void		echo_tokens(t_mshell *msh, t_tokenlist *token);

//	com_exit.c
void		exec_exit(t_mshell *msh, t_tokenlist *token);

//	com_export.c
void		export_var(t_mshell *msh, t_tokenlist *token, t_vscope scope);

//	com_unset.c
void		unset(t_mshell *msh);

#endif
