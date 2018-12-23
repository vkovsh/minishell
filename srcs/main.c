#include "minishell.h"

int	main(void)
{
	t_string *prompt = create_prompt();
	t_string *command = (t_string *)malloc(sizeof(t_string));
	t_shellinfo	si;

	init_shellinfo(&si);
	display_prompt(prompt);
	while (get_next_line(0, &command->str))
	{
		command->size = ft_strlen(command->str);
		//if (!lexer(command))
		//	ft_printf("OK\n");
		//	processor(command);
		display_prompt(prompt);
	}
	delete_string(prompt);
	return (0);
}