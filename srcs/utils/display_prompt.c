#include "minishell.h"

void		display_prompt(t_string *prompt)
{
	write(1, prompt->str, prompt->size);
}