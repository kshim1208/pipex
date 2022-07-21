/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:12:50 by kshim             #+#    #+#             */
/*   Updated: 2022/07/21 13:50:07 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "stdio.h"
#include "stdlib.h"
#include "../libft/ft_printf.h"

int	main(int argc, char **argv, char **envp)
{
	t_ft_px_data	*px_data;

	px_data = ft_px_init_px_data(argc, argv, envp);
	if (argc >= 5)
		ft_px_pipex(px_data);
	else
	{
		ft_putendl_fd("usage : ./pipex file1 cmd1 ... cmdn file2", 2);
		free_px_data(&px_data);
		exit(1);
	}
	free_px_data(&px_data);
	return (0);
}

void	ft_px_exit_with_message(char *func_name, int msg_index)
{
	char	*message[10];
	char	*err_msg;

	ft_px_set_error_message(message);
	err_msg = ft_strjoin(func_name, message[msg_index]);
	if (err_msg == NULL)
	{
		perror(func_name);
		exit(1);
	}
	perror(err_msg);
	free(err_msg);
	exit(1);
}

void	ft_px_set_error_message(char *message[])
{
	message[FAIL_MALLOC] = " : fail to allocate memory";
	message[FAIL_FORK] = " : fail to fork()";
	message[FAIL_PIPE] = " : fail to pipe()";
	message[FAIL_CLOSE] = " : fail to close()";
	message[FAIL_WAIT] = " : fail to wait()";
	message[FAIL_REDRCT] = " : fail to redirect";
	message[FAIL_EXECVE] = " : fail to execve()";
	message[FAIL_NO_FILE] = " : pipex : No such file or directory";
	message[FAIL_OPEN_FILE] = " : fail to open() file";
	message[FAIL_PARSE_ENVP] = " : fail to parse PATH for envp";
	return ;
}
