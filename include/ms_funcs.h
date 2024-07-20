/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/20 15:50:42 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCS_H
# define MS_FUNCS_H

//	tokenize.c
void		tokenize(t_tokenlist **tokens, char *str);

//	tokenlist.c
void		tokens_print(t_tokenlist **tokens);
t_tokenlist	*token_last(t_tokenlist **tokens);
int			token_new(t_tokenlist **tokens, char *token, int pos);
void		token_clear(t_tokenlist **tokens);

//	envfuncs.c
t_envlist	*env_last(t_envlist **envlist);
void		env_print(t_envlist **envlist);
char		*env_get(t_envlist **envlist, const char *search);
void		env_set(t_envlist **envlist, \
				const char *search, const char *newval);

//	envlist.c
void		env_init(t_envlist **envlist, char *env[]);
int			env_new(t_envlist **envlist, char *param, char *value);
void		env_clear(t_envlist **envlist);

#endif
