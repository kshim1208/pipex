/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:12:50 by kshim             #+#    #+#             */
/*   Updated: 2022/07/15 17:18:51 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

#include "../libft/ft_printf.h"

static int	pipex(t_ft_px_data *px_data, int argc, char **argv, char **envp);
static void	free_px_data(t_ft_px_data *px_data);
static void	free_splitted(char **strs);

/* error code는 어쩔까? */
int	main(int argc, char **argv, char **envp)
{
	t_ft_px_data	*px_data;

	px_data = ft_px_init_px_data(argc, envp);
	if (px_data == NULL)
	{
		return (1);
	}
	if (argc >= 6 && ft_px_is_here_doc(argv[1], px_data) == 1)
	{
		pipex(px_data, argc, argv, envp);
	}
	else if (argc >= 5)
	{
		pipex(px_data, argc, argv, envp);
	}
	else
	{
		/*error 출력 및 exit? or return (1)? */
	}
	return (0);
}

static int	pipex(t_ft_px_data *px_data, int argc, char **argv, char **envp)
{
	int		pipe_old;
	int		pipe_new;
	int		fd[4];
	int		pid;

	px_data -> cmd_n = 1;
	if (px_data -> is_here_doc == 1)
		px_data -> cmd_last = argc - 4;
	else
		px_data -> cmd_last = argc - 3;
	while ((px_data -> cmd_n) <= (px_data -> cmd_last))
	{
		if ((px_data -> cmd_n) % 2 == 1)
		{	
			pipe_old = 2;
			pipe_new = 0;
		}
		else
		{
			pipe_old = 0;
			pipe_new = 2;
		}
		if (px_data -> cmd_n != px_data -> cmd_last)
		{
			pipe(&(fd[pipe_new]));
		}
		pid = fork();
		if (pid < 0)
		{
			/* error-free func */
			return (1);
		}
		else if (pid > 0)
		{
			/* 부모 */
			if (px_data -> cmd_n != px_data -> cmd_last)
			{
				close(fd[pipe_new + 1]);
			}
			if (px_data -> cmd_n != 1) 
			{
				close(fd[pipe_old]);
			}
		}
		else
		{
			/* 자식 */
			if (px_data -> cmd_n == px_data -> cmd_last)
			{
				dup2(fd[pipe_old], 0);
				close(fd[pipe_old]);
				if (!ft_px_output_file(argv[argc - 1]))
				{
					return (1);
				}
			}
			else if (px_data -> cmd_n == 1)
			{
				close(fd[pipe_new]);
				if (!ft_px_input_file(argv[1]))
				{
					return (1);
				}
				dup2(fd[pipe_new + 1], 1);
				close(fd[pipe_new + 1]);
			}
			else
			{
				close(fd[pipe_new]);
				dup2(fd[pipe_old], 0);
				close(fd[pipe_old]);
				dup2(fd[pipe_new + 1], 1);
				close(fd[pipe_new + 1]);
			}
			if (!(ft_px_check_command(argv[px_data -> cmd_n + 1], px_data)))
			{
				/* error */
				return (1);
			}
			if (execve(px_data -> cmd_paths, px_data -> cmd_argv, envp) < 0)
			{
				/* 오류 리턴 상황 확인 */
				/* execve 실패 시 -1 반환하고 errno 설정함 */
				/* free */
				return (1);
			}
		}
		/* cmd parsing을 자식 프로세스에서 하고 있어서 해제 아예 안해도 될지도 모른다 */
		/* 아니면 오히려 부모에서 할당하고 해제하는게 나중에 코드 수정할 때 직관적일까? */
		if (px_data -> cmd_paths != NULL)
		{
			free(px_data -> cmd_paths);
			px_data -> cmd_paths = NULL;
			if (px_data -> cmd_argv != NULL)
				free_splitted(px_data -> cmd_argv);
			px_data -> cmd_argv = NULL;
		}
		px_data -> cmd_n++;
	}
	px_data -> cmd_n = 1;
	while ((px_data -> cmd_n) <= (px_data -> cmd_last))
	{
		wait(NULL);
		px_data -> cmd_n++;
	}
	free_px_data(px_data);
}

void	free_px_data(t_ft_px_data *px_data)
{
	free(px_data -> cmd_paths);
	px_data -> cmd_paths = NULL;
	if (px_data -> cmd_argv != NULL)
		free_splitted(px_data -> cmd_argv);
	px_data -> cmd_argv = NULL;
	if (px_data -> paths != NULL)	
		free_splitted(px_data -> paths);
	px_data -> paths = NULL;
	free(px_data);
	return ;
}

void	free_splitted(char **strs)
{
	int	i;
      
	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	return ;
}

	/*
	ft_px_check_files(argv, px_data);
*/
	/* 	
		보너스를 할 예정. 따라서 파이프가 몇 개 들어올지 알 수 없으므로 argc 체크는 일단 생략
		
		<프로그램 1[argv[0]], 프로그램 2(argv[argc])>
		주어진 프로그램 1을 읽을 수 있어야 하고, 프로그램 2에 쓰는게 가능해야 pipex를 수행할 수 있으니 반드시 access로 검사해야함.
		here_doc일 경우, 다른 방식 채택 필요 -> here_doc 공부하기
		access의 첫번째 인자가 경로이므로 주어진 프로그램의 경로가 반드시 필요함.
		*/