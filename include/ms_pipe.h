/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/07/24 17:31:21 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include <sys/types.h>
#include <sys/wait.h>

# define ERR_INFILE "No such file or directory\n"
# define ERR_OUTFILE "No such file or directory\n"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe wasn't created\n"
# define ERR_CMD "Command not found\n"
# define ERR_MEMORY "Not enough memory for struct\n"
# define ERR_EXEC "Execution didn't work\n"
# define ERR_FORK "Fork wasnt created\n"
# define ERR_WAIT "Something happened with child process\n"

#endif
