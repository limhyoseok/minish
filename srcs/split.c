#include "../include/minishell.h"

int get_double_pointer_len(char ** arg)
{
    int i = 0;
    while (arg[i] != NULL)
    {
        //printf("%s \n",arg[i]);
        i++;
    }
    return (i);
}

void split_semicolon(char * input)
{
    char **splited_semi = ft_split(input, ';');
    // int splited_len;
    // splited_len = get_double_pointer_len(splited_semi);
    
    if(splited_semi == NULL)
        return;

    int i = 0;
    while (splited_semi[i] != NULL)
    {
        split_pipe(splited_semi[i]);
        i++;
    }
    //ft_putendl_fd("3", 1);
}

void split_pipe(char * input)
{
    char **splited_pipe = ft_split(input, '|');
    if(splited_pipe == NULL)
        return;
    int splited_len;
    splited_len = get_double_pointer_len(splited_pipe);

    // int fd[2];
	// pipe(fd);
    
    if(splited_len == 1)
        split_OUTredirection(splited_pipe[0]);

}

// > 를 기준으로 쪼갠다.
void split_OUTredirection(char * input)
{
    char **splited_out = ft_split(input, '>');
    if(splited_out == NULL)
        return;
    // > 오른쪽에 값의 유무로.
    // fd 설정 필요하다.
    int splited_len;
    splited_len = get_double_pointer_len(splited_out);
    
    char *file_name;
    int fd;
    
    if (splited_len > 1)
    {
        //printf("splited_outlen : %d\n", splited_len);
        int i;
        i = 1;
        while (i < splited_len)
        {
            file_name = split_space(splited_out[i])[0];
            //ft_putendl_fd(file_name, 1);

            fd = open(file_name, O_RDWR | O_CREAT, 0744);
            if ((i + 1 == splited_len))
                dup2(fd , 1);
            close(fd);
            i++;
        }
    }

    if(splited_len >= 1)
        split_INredirection(splited_out[0]);
}

// > 기준 왼쪽을 <로 쪼갠다.
void split_INredirection(char * input)
{
    //ft_putstr_fd("input", 1);

    //ft_putendl_fd(input, 1);

    char **splited_in = ft_split(input, '<');
    // if(splited_in == NULL)
    //     return;
    int splited_len;
    splited_len = get_double_pointer_len(splited_in);

    char *file_name;
    int fd;
    if (splited_len > 1)
    {
        int i;
        i = 1;
        while (i < splited_len)
        {
            //ft_putstr_fd("change fd 0", 1);

            file_name = split_space(splited_in[i])[0];
            fd = open(file_name, O_RDONLY);
            if ((i + 1 == splited_len))
                dup2(fd , 0);
            close(fd);
            i++;
        }
    }

    if (splited_len >= 1)
    {
        char **command = split_space(splited_in[0]);
        if(command == NULL)
            return;
        run_command(command);
    }
}

char **split_space(char * input)
{
    //ft_putendl_fd(input, 2);

    char **arr = ft_split(input, ' ');
    return (arr);
}