#include "libft.h"

int             ft_isstrin(const char *haystack, const char *needle)
{
    size_t      diff;
    const char  *substr = ft_strstr(haystack, needle);
    
    if (substr != NULL)
        return (0);//match
    diff = ft_strcmp(haystack, needle);
    return (diff);
}