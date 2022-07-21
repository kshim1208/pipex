/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:32:16 by kshim             #+#    #+#             */
/*   Updated: 2022/07/21 13:49:13 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

typedef struct s_pipex_data{
	int		argc;
	char	**argv;
	char	**envp;
	int		fd_here_doc;
	int		cmd_n;
	int		cmd_last;
	int		pipe_old;
	int		pipe_new;
	int		fd[4];
	int		pid;
	char	**paths;
	char	*cmd_paths;
	char	**cmd_argv;
}				t_ft_px_data;

typedef enum e_error_index{
	FAIL_MALLOC = 0,
	FAIL_HERE_DOC,
	FAIL_GNL,
	FAIL_FORK,
	FAIL_PIPE,
	FAIL_CLOSE,
	FAIL_WAIT,
	FAIL_REDRCT,
	FAIL_EXECVE,
	FAIL_NO_FILE,
	FAIL_OPEN_FILE,
	FAIL_PARSE_ENVP
}			t_ft_px_error_idx;

void			ft_px_pipex(t_ft_px_data *px_data);
void			ft_px_set_pipe(t_ft_px_data *px_data);
void			ft_px_task_parent(t_ft_px_data *px_data);
void			ft_px_wait_on_child(t_ft_px_data *px_data);

void			ft_px_task_children(t_ft_px_data *px_data);
void			ft_px_task_child_io_file(t_ft_px_data *px_data);

int				ft_px_is_here_doc(t_ft_px_data *px_data);
void			ft_px_write_tmp_here_doc(t_ft_px_data *px_data);

t_ft_px_data	*ft_px_init_px_data(int argc, char **argv, char **envp);
void			ft_px_init_paths(char **envp, t_ft_px_data *px_data);
void			ft_px_parse_paths(char *path_pos, t_ft_px_data *px_data);
void			free_px_data(t_ft_px_data **px_data);
void			free_splitted(char **strs);

void			ft_px_input_file(t_ft_px_data *px_data);
void			ft_px_output_file(t_ft_px_data *px_data);
void			ft_px_check_command(char *cmd_wth_optn, t_ft_px_data *px_data);

void			ft_px_exit_with_message(char *func_name, int msg_index);
void			ft_px_set_error_message(char *message[]);

#endif
