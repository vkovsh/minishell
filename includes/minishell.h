#ifndef MINISHELL_H
# define MINISHELL_H

typedef	unsigned long size_t;
typedef struct s_list t_list;
typedef struct s_dictionary t_dictionary;
typedef struct s_string t_string;
typedef struct s_shellinfo shell;
typedef struct s_cmd cmd;
typedef enum e_retcode t_retcode;

extern struct termios	g_init;
extern struct termios	g_raw;

t_retcode	disable_raw_mode(void);
t_retcode	get_init_mode(void);
void		set_raw_mode(void);
t_retcode	enable_raw_mode(void);

t_retcode   init_terminal_data(void);
t_retcode   term_goto(int x, int y);

extern char	*g_clear_str;
extern char	*g_goto_str;
extern char	*g_standout_begin_str;
extern char	*g_standout_end_str;
extern char	*g_key_up_str;
extern char	*g_key_down_str;
extern char	*g_key_left_str;
extern char	*g_key_right_str;

/*
** Command processor prototype
*/
typedef t_retcode	(*t_processor)(shell *shell, cmd *cmd);

/*
** cmd - t_cmd struct
** Returns 0 on success and 1 if fails
*/
t_retcode			clear_processor(shell *s, cmd *c);
t_retcode			pwd_processor(shell *s, cmd *c);
t_retcode			echo_processor(shell *s, cmd *c);
t_retcode			cd_processor(shell *s, cmd *c);
t_retcode			setenv_processor(shell *s, cmd *c);
t_retcode			unsetenv_processor(shell *s, cmd *c);
t_retcode			env_processor(shell *s, cmd *c);
t_retcode			exit_processor(shell *s, cmd *c);
t_retcode			arbitrary_processor(shell *s, cmd *c);

/*
** Function for parsing command text
** Returns a list of t_cmd structures
*/
t_list				*lexer(const char *cmd_txt, shell *s);

/*
** Function for creation command entity of type t_cmd
*/
cmd					create_command(const char *cmd_txt, shell *s);

/*
** Deletes command entity
*/
void				delete_command(cmd *cmd);

/*
** Executes list of commands
*/
t_retcode			exec(void *shell, t_list *commands);

t_string			*create_prompt(const char *dir_name);
void				display_prompt(t_string *prompt);
void				init_shellinfo(shell *si, char **ev);
void				delete_shellinfo(shell *s);
void				delete_args_array(char **arr);
void				signal_handler(int sig_num);

t_retcode           load_history(shell *s);
t_retcode           add_to_history(cmd *cmd, shell *s);

char				*exec_bin_path(const char *bin_name,
						char **path);

#endif