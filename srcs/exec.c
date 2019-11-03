/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 03:24:22 by afrancoi          #+#    #+#             */
/*   Updated: 2019/11/03 02:47:13 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

static int		ft_exec(char *path, char **cmds)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (!*(cmds + 1))
			ft_strncpy(*cmds, ".", 2);
		if (execve(path, cmds, g_env) == -1)
			ft_putendl("Error on execcve");
		else
			return (1);
	}
	wait(&pid);
	return (0);
}

static void		ft_error(char *msg, char *path)
{
	ft_putstr("minishell: ");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putendl(msg);
}

static int		ft_search(char *path, char **cmds)
{
	DIR				*dir;
	struct dirent	*file;
	char			*full_path;

	if (!(dir = opendir(path)))
	{
		ft_error("not a valid directory path", path);
		return (0);
	}
	while ((file = readdir(dir)))
	{
		if (ft_strequ(file->d_name, cmds[0]))
		{
			if (!(full_path = ft_pathjoin(path, file->d_name)))
				break ;
			closedir(dir);
			ft_exec(full_path, cmds);
			ft_strdel(&full_path);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static int		ft_searchbin_arr(char **paths, char **cmds)
{
	int i;

	i = -1;
	while (paths[++i])
	{
		if (ft_search(paths[i], cmds))
			return (1);
	}
	return (0);
}

int				ft_searchbin(char **cmds)
{
	char	*path;
	char	**paths_env;
	int		ret;

	ret = 0;
	paths_env = NULL;
	if (ft_strchr(*cmds, '/'))
	{
		path = ft_strsub(cmds[0], 0, ft_strirchr(cmds[0], '/'));
		ft_strcpy(cmds[0], cmds[0] + ft_strirchr(cmds[0], '/') + 1);
		ret = ft_search(path, cmds);
		ft_strdel(&path);
	}
	else
	{
		if ((path = ft_get_env("PATH")))
		{
			if (!(paths_env = ft_strsplit(path, ":")))
				return (0);
			ret = ft_searchbin_arr(paths_env, cmds);
			ft_del_arrays(paths_env);
		}
	}
	ret ? NULL : ft_error("no such file or directory", cmds[0]);
	return (ret);
}
