/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:32:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 14:37:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "libft.h"

# include <unistd.h>	// non-standard library for POSIX API
# include <fcntl.h>		// file control: open, read, write
# include <fenv.h>		//
# include <stdio.h>		// printf, EOF, FILE, stdin, stdout, stderr
# include <stdlib.h>	// malloc
# include <stdarg.h>	// variadic fucntions
# include <stdbool.h>
# include <string.h>	// NULL definition and string functions
# include <signal.h>	// signal-handling
# include <threads.h>	// threads, mutexes

# include <readline/readline.h>
# include <readline/history.h>

//	tokenize.c
void		tokenize(t_tokenlist **tokens, char *str);

//	tokenlist.c
void		tokens_print(t_tokenlist **tokens);
t_tokenlist	*token_last(t_tokenlist **tokens);
int			token_new(t_tokenlist **tokens, char *token, int pos);
void		token_clear(t_tokenlist **tokens);

//	envlist.c
void		env_print(t_envlist **envlist);
t_envlist	*env_last(t_envlist **envlist);
void		env_init(t_envlist **envlist, char *env[]);
int			env_new(t_envlist **envlist, char *param, char *value);
void		env_clear(t_envlist **envlist);

#endif
