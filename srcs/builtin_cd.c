/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:47:31 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/10 09:32:11 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

static void	ft_cd_err(char *msg, char *path)
{
	ft_putstr("cd: ");
	ft_putstr(msg);
	if (path)
		ft_putendl(path);
	else
		ft_putchar('\n');
}

static int	ft_check_dir(char *path)
{
	struct stat buf;

	if (lstat(path, &buf) == -1)
	{
		ft_cd_err("no such file or directory: ", path);
		return (0);
	}
	if(!(S_ISDIR(buf.st_mode)))
	{
		ft_cd_err("not a directory: ", path);
		return (0);
	}
	if (!(buf.st_mode & S_IXUSR))
	{
		ft_cd_err("permission denied: ", path);
		return (0);
	}
	return (1);
}

static int	ft_change_dir(char *path)
{
	char	cwd[PATH_MAX + 1];
	char	*tmp;

	getcwd(cwd, PATH_MAX);
	if (!cwd[0])
		return (0);
	if (!ft_check_dir(path))
		return (0);
	if (chdir(path) == -1)
	{
		ft_putendl("chdir failed\n");
		return (0);
	}
	if(*path == '/' || *path == '.')
		tmp = path;
	else
		tmp = ft_pathjoin(cwd, path);
	ft_setenv("OLDPWD", cwd);
	ft_setenv("PWD", tmp);
	if(*path != '/' && *path != '.')
		ft_strdel(&tmp);
	return (1);
}

void		ft_builtin_cd(char **args)
{
	char	*path;

	path = NULL;
	if (!args[0])
	{
		if (!(path = ft_get_env("HOME")))
		{
			ft_cd_err("Env \"HOME\" is not defined, no enough arguments.", NULL);
			return ;
		}
	}
	else if (*args[0] == '-')
	{
		if(!(path = ft_get_env("OLDPWD")))
		{
			ft_cd_err("Env \"OLDPWD\" is not defined, cannot use \'-\'.", NULL);
			return ;
		}
	}
	else
		path = args[0];
	if (!(ft_change_dir(path)))
		return ;
}
