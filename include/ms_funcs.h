/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/15 12:45:09 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCS_H
# define MS_FUNCS_H

//	utils.c
bool		is_trailspace(char c);	//	will also return true at end of string
bool		is_whitespace(char c);

//	shell.c
void		shell_free(t_mshell *msh);
void		shell_set_envptrs(t_mshell *msh);
void		shell_init(t_mshell *msh);

//	input.c
int			exec_builtin(t_mshell *msh, t_tokenlist *token);
void		free_pipex(t_pipex *pipex);
void		input_cleanup(t_mshell *msh);
void		input_cycle(t_mshell *msh);

#endif
