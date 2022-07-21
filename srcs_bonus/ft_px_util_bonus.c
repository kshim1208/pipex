/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:46:21 by kshim             #+#    #+#             */
/*   Updated: 2022/07/21 13:52:59 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../libft/libft.h"

t_ft_px_data	*ft_px_init_px_data(int argc, char **argv, char **envp)
{
	t_ft_px_data	*px_data;

	px_data = (t_ft_px_data *)malloc(sizeof(t_ft_px_data));
	if (px_data == 0)
		ft_px_exit_with_message("ft_px_init_px_data", FAIL_MALLOC);
	px_data -> fd_here_doc = -1;
	px_data -> argc = argc;
	px_data -> argv = argv;
	px_data -> envp = envp;
	px_data -> cmd_n = 1;
	px_data -> cmd_last = argc - 3;
	px_data -> cmd_paths = 0;
	px_data -> cmd_argv = 0;
	ft_px_init_paths(envp, px_data);
	return (px_data);
}

void	ft_px_init_paths(char **envp, t_ft_px_data *px_data)
{
	char	*path_pos;
	int		i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == 0)
		ft_px_exit_with_message("ft_px_init_paths", FAIL_PARSE_ENVP);
	path_pos = envp[i] + 5;
	ft_px_parse_paths(path_pos, px_data);
}

void	ft_px_parse_paths(char *path_pos, t_ft_px_data *px_data)
{
	int		i;
	char	*tmp;

	px_data -> paths = ft_split(path_pos, ':');
	if (px_data -> paths == 0)
		ft_px_exit_with_message("ft_px_init_paths", FAIL_MALLOC);
	i = 0;
	while ((px_data -> paths)[i] != 0)
	{
		tmp = ft_strjoin((px_data -> paths)[i], "/");
		if (tmp == 0)
			ft_px_exit_with_message("ft_px_init_paths", FAIL_MALLOC);
		free((px_data -> paths)[i]);
		(px_data -> paths)[i] = tmp;
		i++;
	}
	return ;
}

void	free_px_data(t_ft_px_data **px_data)
{
	t_ft_px_data	*tmp;

	tmp = *px_data;
	if (tmp -> paths != 0)
		free_splitted(tmp -> paths);
	tmp -> paths = 0;
	free(tmp);
	return ;
}

void	free_splitted(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		strs[i] = 0;
		i++;
	}
	free(strs);
	return ;
}
