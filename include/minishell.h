/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:32:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 13:58:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# include "ms_globals.h"
# include "ms_enums.h"
# include "ms_structs.h"

# include "ms_builtins.h"
# include "ms_env.h"
# include "ms_exec.h"
# include "ms_funcs.h"
# include "ms_redirect.h"
# include "ms_tokens.h"

#endif
