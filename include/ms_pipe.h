/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/07/22 15:16:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include <sys/types.h>
#include <sys/wait.h>

# define ERR_INFILE "No such file or directory"
# define ERR_OUTFILE "No such file or directory"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_MEMORY "Not enough memory for struct"
# define ERR_EXEC "Execution didn't work"

#endif
