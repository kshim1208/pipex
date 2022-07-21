/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:27:50 by kshim             #+#    #+#             */
/*   Updated: 2022/07/21 13:52:54 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/get_next_line_bonus.h"
#include "../libft/libft.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"

int	ft_px_is_here_doc(t_ft_px_data *px_data)
{
	if (ft_strncmp(px_data -> argv[1], "here_doc\0", 9) == 0)
	{
		(px_data -> cmd_last)--;
		px_data -> fd_here_doc = open(
				"./.here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (px_data -> fd_here_doc == -1)
			ft_px_exit_with_message("ft_px_is_here_doc", FAIL_HERE_DOC);
		ft_px_write_tmp_here_doc(px_data);
	}
	else
	{
		return (0);
	}
	return (1);
}

void	ft_px_write_tmp_here_doc(t_ft_px_data *px_data)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strjoin(px_data -> argv[2], "\n");
	if (tmp == 0)
		ft_px_exit_with_message("ft_px_write_tmp_here_doc", FAIL_MALLOC);
	while (1)
	{
		buf = get_next_line(0);
		if (buf == 0)
			ft_px_exit_with_message("ft_px_write_tmp_here_doc", FAIL_GNL);
		if (ft_strcmp(buf, tmp) == 0)
		{
			free(buf);
			free(tmp);
			return ;
		}
		write(px_data -> fd_here_doc, buf, ft_strlen(buf));
		free(buf);
	}
	close(px_data -> fd_here_doc);
	return ;
}
