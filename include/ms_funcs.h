/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 14:11:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCS_H
# define MS_FUNCS_H

//pipe_0.c
void		ft_pipe_init(t_tokenlist *tokens, char *ptr, char *env[]);

//pipe_1.c
char		*find_path(char **envp);
void		struct_init(t_pipex *pipex, char *envp[]);
void		ft_pipe(int num_pipes ,char *pipe_arg[], char *env[]);

//pipe_utils.c
void		close_pipes(t_pipex *pipex);
int			msg(char *err);
void		msg_error(char *err, t_pipex *pipex);
void		parent_free(t_pipex *pipex);
void		child_free(t_pipex *pipex);

//pipe_child.c
char		*get_cmd(char **paths, char *cmd);
void		first_child(t_pipex *pipex, char *av[], char *envp[]);
void		middle_child(t_pipex *pipex, char *av[], char *envp[]);
void		last_child(t_pipex *pipex, char *av[], char *envp[]);

//	tokenize.c
void		tokenize(t_tokenlist **tokens, char *str);

//	tokenlist.c
void		tokens_print(t_tokenlist **tokens);
t_tokenlist	*token_last(t_tokenlist **tokens);
int			token_addvar(t_tokenlist *token, char *str);
int			token_new(t_tokenlist **tokens, char *token, char *str, int pos);
void		token_clear(t_tokenlist **tokens);

//	tokenfuncs.c
t_tokenlist	*token_at_pos(t_tokenlist **tokens, int serachpos);
int			token_count_type(t_tokenlist **tokens, char *metachar);
void		token_pos_type(t_tokenlist **tokens, int **pos, char *metachar);

//	envfuncs.c
t_envlist	*env_last(t_envlist **envlist);
void		env_print(t_envlist **envlist);
t_envlist	*env_get_ptr(t_envlist **envlist, const char *search);
char		**env_get_val(t_envlist **envlist, const char *search);
void		env_set(t_envlist **envlist, \
				const char *search, const char *newval);

//	envlist.c
void		env_clear(t_envlist **envlist);
void		env_del(t_envlist **envlist);
int			env_new(t_envlist **envlist, char *param, char *value);

//	envinit.c
void		env_init(t_envlist **envlist, char *env[]);

//	utils.c
bool		is_whitespace(char c);

//	expand.c
char		**expand_variable(t_envlist **envlist, char *param);

#endif
