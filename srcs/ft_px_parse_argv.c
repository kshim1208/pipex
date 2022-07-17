/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_parse_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:35:45 by kshim             #+#    #+#             */
/*   Updated: 2022/07/14 15:40:06 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 차후 조건으로 here_doc 감지 만들기 */
#include "../include/pipex.h"
#include "../libft/libft.h"

	/* access로 파일 존재 및 읽기 권한 필요 (실행은?) 
	 마지막 파일에는 파일 존재 및 쓰기 권한 필요 (실행이랑 읽기는?) */


int	ft_px_input_file(char *i_file)
{
	if (access(i_file, F_OK | R_OK) == 0)
	{
		int	fd_in;

		fd_in = -1;
		fd_in = open(i_file, O_RDONLY);
		if (fd_in == -1)
			return (0);
		dup2(fd_in, 0);
		close(fd_in);
	}
	else
	{
		/* stdin 없으면 그냥 없는거니까 함수 종료? */
		/* 아니면 stdin 비우고 동작하게 만들기? */
	}
	return (1);
}

int	ft_px_output_file(char *o_file)
{
	int	fd_out;

	fd_out = -1;
	fd_out = open(o_file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_out == -1)
		return (0);
	dup2(fd_out, 1);
	close(fd_out);
		/* 새로 파일 만듬 -> stdout의 기본 기능인가? 찾아보기 */
		/* bash에서는 file로 redirect할 때 파일이 없으면 새로 만든다. */
		/* open 함수에 O_CREAT 옵션 주면 파일이 없을 때 만들 수 있다. */
		/* O_TRUNC 옵션 쓰는 사람 있던데 기능 좀 파악해보기 */
		/* -> 이미 있는 파일이고, 쓰기 가능이라면 현재 파일 내용 삭제하고 길이 0으로 만들기 */
		/* bash 동작이랑 비교 */
		/* 원래 존재하는 파일이라면 내용 지우고 쓰는 것으로 보임. O_TRUNC 옵션 추가하자 */

		/* 파일 만들면서 동시에 권한도 줄 수는 없나? 하나하나 chmod하기 불편한데 */
		/* O_CREAT 할 때 권한 줄 수 있었음. open() 참고 */

	return (1);
}

/* 반복문 안에서 해당 cmd 실행됬을 때만 parsing하기 */
/* access 안쓰고 할거면 do command도 괜찮지 않으려나 */
int	ft_px_check_command(char *cmd_wth_optn, t_ft_px_data *px_data)
{
	char	*cmd_wth_path;
	int		i;

	px_data -> cmd_argv = ft_split(cmd_wth_optn, ' ');
	if ((px_data -> cmd_argv) == NULL)
		return (0);
	i = 0;
	px_data -> cmd_paths = NULL;
	while ((px_data -> paths)[i] != NULL)
	{
		cmd_wth_path = ft_strjoin(
				(px_data -> paths)[i], (px_data -> cmd_argv)[0]);
		if (cmd_wth_path == NULL)
			return (0);
		if (access(cmd_wth_path, F_OK | X_OK) == 0)
		{
			px_data -> cmd_paths = cmd_wth_path;
			return (1);
		}
		i++;
		free(cmd_wth_path);
	}
	/* 적절한 cmd가 아닌 경우에는? - 지금 NULL임. */
	return (1);
}

/* access 없이 바로 execve해도 괜찮을 것 같음. */
/* execve 실패하면 해당 커맨드는 실행하지 않고 다음 커맨드에 input 넘기기 */