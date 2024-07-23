/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 14:44:58 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define MS_FUNCS_H

//exec_cmd.c
void		pipe_args_fill(int num_pipes, int *pipe_pos, char **pipe_arg[], char *ptr);
void		struct_init(t_pipex *pipex, char *envp[], int num_pipes);
void		ft_exec_cmd(t_pipex *pipex, char *av, char **env);
void		ft_exec_init(t_tokenlist *tokens, char *ptr, char *env[]);

//pipe.c

//exec_utils.c
char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
void	free_pipex(t_pipex *pipex);

// not needed || will be replaced by universal msg_error
void	msg_error(char *err, t_pipex *pipex);
int		msg(char *err);


//pipe_child.c


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
char		**env_get(t_envlist **envlist, const char *search);
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
