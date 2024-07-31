/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:41:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/31 15:42:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

//	cd.c
void		change_dir(t_mshell *msh, char *newdir);

//	echo_token.c
void		echo_tokens(t_mshell *msh, int fd);

//	echo.c
void		echo_expand_str(t_mshell *msh, char *str, int fd);

//	expand.c
char		**expand_variable(t_envlist **envlist, char *param);

//	export.c
void		export_var(t_mshell *msh);

//	unset.c
void		unset(t_mshell *msh);

#endif
