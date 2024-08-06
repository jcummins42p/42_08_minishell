/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:47:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/06 16:15:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOKENS_H
# define MS_TOKENS_H

//	token_typechecks.c - check a string for its function in the shell
int			is_assign(char *str);	//	if a=2, returns index of = operator
int			is_metachar(char *str);	//	return t_mtctype of string
int			is_builtin(char *str);	//	return t_comtype of string

//	token_expand.c
char 		*expand_string_sq(char *input);
char 		*expand_string_dq(t_mshell *msh, char *input);

//	new_tokenize.c
int			new_token_parse(t_mshell *msh, int end);
void		new_tokenize(t_mshell *msh);

//	tokenize.c
int			tokenize(t_mshell *msh);

//	token_init.c
int			token_new(t_mshell *msh, char *newtoken, int pos);

//	token_list.c
void		token_clear(t_tokenlist **tokens);
t_tokenlist	*token_at_index(t_tokenlist **tokens, int search);
t_tokenlist	*token_last(t_tokenlist **tokens);

//	token_print.c
void		token_print(t_tokenlist *token);
void		tokens_print_list(t_tokenlist **tokens);

//	tokenfuncs.c
void		tokens_get_info(t_mshell *msh);
t_tokenlist	*token_after_pipeno(t_tokenlist **tokens, int pipe_no);
t_tokenlist	*token_at_pos(t_tokenlist **tokens, int serachpos);
int			token_count_type(t_tokenlist **tokens, char *metachar);
void		token_pos_type(t_tokenlist **tokens, int **pos, char *metachar);

//	token_parse.c
int			token_parse_generic(t_mshell *msh, int *end);
int			token_parse_metachar(t_mshell *msh, int *i);
int			token_parse_builtin(t_mshell *msh, int *i);

#endif
