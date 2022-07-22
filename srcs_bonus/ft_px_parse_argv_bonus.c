/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_parse_argv_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:35:45 by kshim             #+#    #+#             */
/*   Updated: 2022/07/22 09:32:15 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "../libft/ft_printf.h"

void	ft_px_input_file(t_ft_px_data *px_data)
{
	int	fd_in;

	fd_in = -1;
	if (px_data -> fd_here_doc != -1)
	{
		fd_in = open("./.here_doc.tmp", O_RDONLY);
		unlink("./.here_doc.tmp");
	}
	else
	{
		if (access(px_data -> argv[1], F_OK | R_OK) == 0)
			fd_in = open(px_data -> argv[1], O_RDONLY);
		else
			ft_px_exit_with_message("ft_px_input_fle", FAIL_NO_FILE);
	}
	if (fd_in == -1)
		ft_px_exit_with_message("ft_px_pipex", FAIL_OPEN_FILE);
	if (dup2(fd_in, 0) < 0
		|| close(fd_in) < 0)
		ft_px_exit_with_message("ft_px_pipex", FAIL_REDRCT);
	return ;
}

void	ft_px_output_file(t_ft_px_data *px_data)
{
	int	fd_out;

	fd_out = -1;
	if (px_data -> fd_here_doc != -1)
		fd_out = open(px_data -> argv[px_data -> argc - 1],
				O_CREAT | O_APPEND | O_WRONLY, 0666);
	else
		fd_out = open(px_data -> argv[px_data -> argc - 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_out == -1)
		ft_px_exit_with_message("ft_px_pipex", FAIL_OPEN_FILE);
	if (dup2(fd_out, 1) < 0
		|| close(fd_out) < 0)
		ft_px_exit_with_message("ft_px_pipex", FAIL_REDRCT);
	return ;
}

void	ft_px_check_command(char *cmd_wth_optn, t_ft_px_data *px_data)
{
	char	*cmd_wth_path;
	int		i;

	px_data -> cmd_argv = ft_split(cmd_wth_optn, ' ');
	if ((px_data -> cmd_argv) == 0)
		ft_px_exit_with_message("ft_px_check_command", FAIL_MALLOC);
	i = 0;
	while ((px_data -> paths)[i] != 0)
	{
		cmd_wth_path = ft_strjoin(
				(px_data -> paths)[i], (px_data -> cmd_argv)[0]);
		if (cmd_wth_path == 0)
			ft_px_exit_with_message("ft_px_check_command", FAIL_MALLOC);
		if (access(cmd_wth_path, F_OK | X_OK) == 0)
		{
			px_data -> cmd_paths = cmd_wth_path;
			return ;
		}
		i++;
		free(cmd_wth_path);
	}
	return ;
}
