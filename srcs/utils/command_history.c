#include "minishell.h"
#include "ft_printf.h"
#include <fcntl.h>

static t_retcode    open_history_file(shell *s)
{
    const char      *home_dir = FIND(s->environ, "HOME", 4);
    char            *filename;

    if (home_dir == NULL)
        return (RC_ERR_HOME_UNSET);
    if (access(home_dir, F_OK | R_OK | W_OK) == -1)
    {
        return (RC_ERR_PERMISSION);
    } 
    filename = ft_strjoin(home_dir, "/.42sh_history");
    ft_printf("%s\n", filename);
    s->history_handler = open(filename,
                        O_RDWR | O_APPEND | O_CREAT,
                        S_IRUSR | S_IWUSR);
    ft_printf("%d\n", s->history_handler);
    if (s->history_handler == -1)
    {
        return (RC_ERR_HISTORY_ACCESS);
    }
    ft_strdel(&filename);
    return (RC_SUCCESS);
}

t_retcode           load_history(shell *s)
{
    t_retcode       ret;
    char            *line;
	t_node          node;

    line = NULL;
    ret = open_history_file(s);
    if (ret != RC_SUCCESS)
    {
        return (ret);
    }
    while (get_next_line(s->history_handler, &line) != 0)
    {
        node = ITEM(line, ft_strlen(line) + 1, "", 1);
        INSERT(s->history, &node);
        ft_strdel(&line);
        line = NULL;    
    }
    return (RC_SUCCESS);
}

t_retcode           add_to_history(t_cmd *cmd, shell *s)
{
    t_node          node;
    const size_t    cmd_len = ft_strlen(cmd->cmd_txt);

    node = ITEM(cmd->cmd_txt, cmd_len + 1, "", 1);
    INSERT(s->history, &node);
    ft_dprintf(s->history_handler, "%s\n", cmd->cmd_txt);
    return (RC_SUCCESS);
}

// t_retcode   search_in_history(const char *cmd, t_dictionary *history)
// {

// }