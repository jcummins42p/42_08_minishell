/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:32:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 18:30:49 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_structs.h"
# include "ms_funcs.h"
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

#endif
