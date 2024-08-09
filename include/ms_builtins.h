/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:41:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/09 15:41:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

//	cd.c
void		change_dir(t_mshell *msh, char *newdir);

//	echo_token.c
void		echo_tokens(t_tokenlist *token, int fd);

//	export.c
void		export_var(t_mshell *msh, t_tokenlist *token, t_vscope scope);

//	unset.c
void		unset(t_mshell *msh);

#endif
