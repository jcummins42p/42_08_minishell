/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 18:00:51 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCS_H
# define MS_FUNCS_H

//	*COMMAND*	//

//	echo.c

//	expand.c
char		**expand_variable(t_envlist **envlist, char *param);

//exec_cmd.c
void		pipe_args_fill(int num_pipes, int *pipe_pos, char **pipe_arg[], char *ptr);
void		struct_init(t_pipex *pipex, char *envp[], int num_pipes);
void		ft_exec_cmd(t_pipex *pipex, char *av, char **env);
void		ft_exec_init(t_tokenlist *tokens, char *ptr, char *env[]);

//	*ENV*	//

//	envfuncs.c
t_envlist	*env_last(t_envlist **envlist);
void		env_print(t_envlist **envlist);

//	envget.c
t_envlist	*env_search(t_envlist **envlist, const char *search);
char		**env_get_val(t_envlist **envlist, const char *search);

//	envinit.c
void		env_init(t_envlist **envlist, char *env[]);

//	envlist.c
void		env_clear(t_envlist **envlist);
void		env_del(t_envlist **envlist);
int			env_new(t_envlist **envlist, char *param, char *value);

//	envset.c
void		env_set(t_envlist **envlist, \
				const char *search, const char *newval);
void		env_unset(t_envlist **envlist, const char *search);

//	*PIPE*	//

//pipe.c
void		ft_pipe(int ac ,char *av[], char *envp[], t_pipex *pipex);
void		handle_exec_error(t_pipex *pipex, const char *error_message);
void		first_child(t_pipex *pipex, char *env[]);
void		last_child(t_pipex *pipex, char *env[]);

//exec_utils.c
char		*find_path(char **envp);
char		*get_cmd(char **paths, char *cmd);
void		free_pipex(t_pipex *pipex);

// not needed || will be replaced by universal msg_error
void		msg_error(char *err, t_pipex *pipex);
int			msg(const char *err);

//	*TOKENS*	//

//	tokenize.c
void		tokenize(t_mshell *msh);

//	tokenlist.c
void		tokens_print(t_tokenlist **tokens);
t_tokenlist	*token_last(t_tokenlist **tokens);
int			token_addvar(t_tokenlist *token, char *str);
int			token_new(t_envlist **envlist, t_tokenlist **tokens, char *token, char *str, int pos);
void		token_clear(t_tokenlist **tokens);

//	tokenfuncs.c
t_tokenlist	*token_at_pos(t_tokenlist **tokens, int serachpos);
int			token_count_type(t_tokenlist **tokens, char *metachar);
void		token_pos_type(t_tokenlist **tokens, int **pos, char *metachar);

//	*MISC*	//

//	utils.c
bool		is_whitespace(char c);

#endif
