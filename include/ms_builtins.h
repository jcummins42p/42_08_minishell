/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:41:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/12 14:19:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

//	cd.c
void		change_dir(t_mshell *msh, t_tokenlist *token);

//	echo_token.c
void		echo_tokens(t_mshell *msh, t_tokenlist *token);

//	export.c
void		export_var(t_mshell *msh, t_tokenlist *token, t_vscope scope);

//	unset.c
void		unset(t_mshell *msh);

#endif
