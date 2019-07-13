/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 03:24:22 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/10 09:35:26 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

/*
**	get env path
**	or current directory
**	search for cmds[0];
**	execute or fail;
*/
static int	ft_exec(char *path, char **cmds)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if(!*(cmds + 1))
		{
			ft_strncpy(*cmds, ".", 2);
			if(execve(path, cmds, g_env) == -1)
				ft_putendl("EXECCVE ERROR");
			else
				return (1);
		}
		else
		{
			if(execve(path, cmds, g_env) == -1)
				ft_putendl("EXECCVE ERROR");
			else
				return (1);
		}

	}
	wait(&pid);
	return (0);
}

static void	ft_error(char *msg, char *path)
{
	ft_putstr("minishell: ");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putendl(msg);
}

static int	ft_search(char *path, char **cmds)
{
	DIR *dir;
	struct dirent *file;
	char	*full_path;

	if(!(dir = opendir(path)))
	{
		ft_error("not a valid env path", path);
		return (0);
	}
	while((file = readdir(dir)))
	{
		if(ft_strequ(file->d_name, cmds[0]))
		{
			if(!(full_path = ft_pathjoin(path, file->d_name)))
			{
				closedir(dir);
				return (0);
			}
			closedir(dir);
			ft_exec(full_path, cmds);
			ft_strdel(&full_path);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int		ft_searchbin(char **cmds)
{
	char	*path;
	char	**paths_env;
	int		ret;
	int		i;

	ret = 0;
	paths_env = NULL;
	if(!(path = ft_get_env("PATH")))
		path = ft_strdup(".");
	if(!ft_strequ(path, "."))
	{
		if(!(paths_env = ft_strsplit(path, ':')))
			return (0);
		i = -1;
		while(paths_env[++i])
		{
			if((ret = ft_search(paths_env[i], cmds)))
				break ;
		}
		if(!ret)
			ft_error("no such file or directory", cmds[0]);
		ft_del_arrays(paths_env);
		return (ret);
	}
	else
	{
		ret = ft_search(path, cmds);
		ft_strdel(&path);
		if(!ret)
			ft_error("no such file or directory", cmds[0]);
		return (ret);
	}
	return (0);
}
