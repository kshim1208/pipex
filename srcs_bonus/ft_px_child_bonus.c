/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:28:40 by kshim             #+#    #+#             */
/*   Updated: 2022/07/22 09:35:20 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <unistd.h>

void	ft_px_task_children(t_ft_px_data *px_data)
{
	if (px_data -> cmd_n == px_data -> cmd_last
		|| px_data -> cmd_n == 1)
		ft_px_task_child_io_file(px_data);
	else
	{
		if (close(px_data -> fd[px_data -> pipe_new]) < 0
			|| dup2(px_data -> fd[px_data -> pipe_old], 0) < 0
			|| close(px_data -> fd[px_data -> pipe_old]) < 0
			|| dup2(px_data -> fd[px_data -> pipe_new + 1], 1) < 0
			|| close(px_data -> fd[px_data -> pipe_new + 1]) < 0)
			ft_px_exit_with_message("ft_px_task_children", FAIL_REDRCT);
	}
	if (px_data -> fd_here_doc != -1)
		ft_px_check_command(px_data -> argv[(px_data -> cmd_n) + 2], px_data);
	else
		ft_px_check_command(px_data -> argv[(px_data -> cmd_n) + 1], px_data);
	if (execve(px_data -> cmd_paths, px_data -> cmd_argv, px_data -> envp) < 0)
		ft_px_exit_with_message("ft_px_task_children", FAIL_EXECVE);
	return ;
}

void	ft_px_task_child_io_file(t_ft_px_data *px_data)
{
	if (px_data -> cmd_n == 1)
	{
		if (close(px_data -> fd[px_data -> pipe_new]) < 0
			|| dup2(px_data -> fd[px_data -> pipe_new + 1], 1) < 0
			|| close(px_data -> fd[px_data -> pipe_new + 1]) < 0)
			ft_px_exit_with_message("ft_px_tash_child_io_file", FAIL_REDRCT);
		ft_px_input_file(px_data);
	}
	else if (px_data -> cmd_n == px_data -> cmd_last)
	{
		if (dup2(px_data -> fd[px_data -> pipe_old], 0) < 0
			|| close(px_data -> fd[px_data -> pipe_old]) < 0)
			ft_px_exit_with_message("ft_px_task_child_io_file", FAIL_REDRCT);
		ft_px_output_file(px_data);
	}
	return ;
}
