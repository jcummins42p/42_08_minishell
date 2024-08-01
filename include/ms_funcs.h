/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 17:27:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCS_H
# define MS_FUNCS_H

//	exec_cmd.c
char		**ft_get_arg_pipe(t_mshell *msh);
void		struct_init(t_mshell *msh);
void		ft_exec_cmd(t_mshell *msh);
void		ft_exec_init(t_mshell *msh);

//	utils.c
bool		is_whitespace(char c);

//	shell.c
void		shell_free(t_mshell *msh);
void		shell_set_envptrs(t_mshell *msh);
void		shell_init(t_mshell *msh);

//	input.c
int			exec_builtin(t_mshell *msh, t_tokenlist *token);
void		input_cycle(t_mshell *msh);

#endif
