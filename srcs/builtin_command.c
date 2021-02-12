#include "../include/minishell.h"

void	ft_echo(char* str)
{
	ft_putstr_fd(str, 1);
}

void	ft_pwd(void)
{
	char	*pwd;
	pwd = getcwd(NULL, 1024);
	ft_putendl_fd(pwd, 1);
}


void	ft_cd(char *path)
{
	chdir(path);
}

void	ft_env()
{
	int i;
	i = 0;
	char ** split_equal;
	while(g_envp[i] != NULL)
	{
		split_equal = ft_split(g_envp[i], '=');
		if (ft_strncmp(g_envp[i], "", 100) != 0 && split_equal[1] != NULL)
			ft_putendl_fd(g_envp[i], 1);
		i++;
	}
}

void	ft_export(char *env)
{
	int i = 0;
	char **split_equal;
	int len = get_double_pointer_len(g_envp);
	//env 유뮤 체크
	if (env == NULL)
	{
		//오름 차순 출력해야한다.
		while(g_envp[i] != NULL)
		{
			split_equal = ft_split(g_envp[i], '=');
			ft_putstr_fd("declare -x ",1);
			ft_putstr_fd(split_equal[0],1);
			if (split_equal[1] != NULL)
			{
				ft_putstr_fd("=\"",1);
				ft_putstr_fd(split_equal[1],1);
				ft_putendl_fd("\"",1);
			}	
			i++;
		}
	}
	else
	{
		while( g_envp[i] != NULL)
		{
			split_equal = ft_split(env, '=');

			if (ft_strncmp(split_equal[0],ft_split(g_envp[i], '=')[0],100) == 0)
			{
				// 기존 값 free 필요
				g_envp[i] = ft_strdup(env);
				ft_putendl_fd("dk",1);
				return;
			}
			i++;
		}
		char **new_envv = (char **)malloc(sizeof(char *) * (len + 2));

		//존재하지 않으면 사이즈 추가시켜야한다.		
	}
}

void	ft_unset(char *env)
{
	int i = 0;
	char **split_equal;
	char **new_envp;
	while( g_envp[i] != NULL)
	{
		split_equal = ft_split(g_envp[i], '=');
		//100아니라 두개의 길이를 비교해줘야한다.
		if (ft_strncmp(env,split_equal[0],100) == 0)
		{
			//시간나면 malloc으로 처리하자
			g_envp[i] = "";
			break;
		}
		i++;
	}
}

void	ft_exit(void)
{
	exit(0);
}
