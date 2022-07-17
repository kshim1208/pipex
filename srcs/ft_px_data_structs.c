/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_data_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:32:54 by kshim             #+#    #+#             */
/*   Updated: 2022/07/15 16:40:27 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_ft_px_data	*ft_px_init_px_data(int argc, char **envp)
{
	t_ft_px_data	*px_data;


	px_data = (t_ft_px_data *)malloc(sizeof(t_ft_px_data));
	if (px_data == NULL)
		return (NULL);
	px_data -> is_here_doc = 0;
	px_data -> cmd_n = 1;
	px_data -> cmd_last = argc - 3;
	px_data -> cmd_paths = NULL;
	px_data -> cmd_argv = NULL;
	if (ft_px_init_paths(envp, px_data) == 0)
		return (NULL);
	return (px_data);
}
