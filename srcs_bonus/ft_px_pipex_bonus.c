/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:13:49 by kshim             #+#    #+#             */
/*   Updated: 2022/07/22 09:32:26 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <unistd.h>
#include <sys/wait.h>

void	ft_px_pipex(t_ft_px_data *px_data)
{
	while ((px_data -> cmd_n) <= (px_data -> cmd_last))
	{
		ft_px_set_pipe(px_data);
		px_data -> pid = fork();
		if (px_data -> pid < 0)
			ft_px_exit_with_message("ft_px_pipex", FAIL_FORK);
		else if (px_data -> pid > 0)
		{
			ft_px_task_parent(px_data);
		}
		else
		{
			ft_px_task_children(px_data);
		}
		(px_data -> cmd_n)++;
	}
	ft_px_wait_on_child(px_data);
	return ;
}

void	ft_px_set_pipe(t_ft_px_data *px_data)
{
	if ((px_data -> cmd_n) % 2 == 1)
	{	
		px_data -> pipe_old = 2;
		px_data -> pipe_new = 0;
	}
	else
	{
		px_data -> pipe_old = 0;
		px_data -> pipe_new = 2;
	}
	if (px_data -> cmd_n != px_data -> cmd_last)
	{
		if (pipe(&(px_data -> fd[px_data -> pipe_new])) < 0)
			ft_px_exit_with_message("ft_px_pipex", FAIL_PIPE);
	}
	return ;
}

void	ft_px_task_parent(t_ft_px_data *px_data)
{
	if (((px_data -> cmd_n != px_data -> cmd_last
				&& close(px_data -> fd[(px_data -> pipe_new) + 1]) < 0))
		|| ((px_data -> cmd_n != 1)
			&& (close(px_data -> fd[px_data -> pipe_old]) < 0)))
		ft_px_exit_with_message("ft_px_pipex", FAIL_CLOSE);
	return ;
}

void	ft_px_wait_on_child(t_ft_px_data *px_data)
{
	px_data -> cmd_n = 1;
	while ((px_data -> cmd_n) <= (px_data -> cmd_last))
	{
		if (wait(0) < 0)
			ft_px_exit_with_message("ft_px_pipex", FAIL_WAIT);
		(px_data -> cmd_n)++;
	}
	return ;
}
