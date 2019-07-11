#include "libft.h"

char        *ft_substrcut(const char *str, const char *sub)
{
    size_t  str_len;
    size_t  sub_len;
    const char *buf = str;
    int     cmp_res;
    char    *new_str;
    size_t  new_str_pos;
    char    *trash;

    if (str == NULL || sub == NULL)
    {
        return (NULL);
    }
    str_len = ft_strlen(str);
    sub_len = ft_strlen(sub);
    if (sub_len == 0)
    {
        return (ft_strdup(str));
    }
    if (sub_len > str_len)
    {
        return (NULL);
    }
    new_str = ft_strnew(str_len);
    new_str_pos = 0;
    while (*buf)
    {
        cmp_res = ft_strncmp(buf, sub, sub_len);
        if (cmp_res != 0)
        {
            str_len--;
            new_str[new_str_pos++] = *buf++;
        }
        else
        {
            if (str_len < sub_len)
            {
                break ;
            }
            str_len -= sub_len;
            buf += sub_len;
        }
    }
    trash = new_str;
    new_str = ft_strdup(new_str);
    ft_strdel(&trash);
    return (new_str);
}