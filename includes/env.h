#ifndef ENV_H
# define ENV_H
# define ENV_I_M 0x01
# define ENV_ZERO_M 0x02
# define ENV_U_M 0x04
# define ENV_C_M 0x08

/*
** 	-i, --ignore-environment
**		start with an empty environment
**
** 	-0, --null
**		end each output line with NUL, not newline
**
**	-u, --unset=NAME
**		remove variable from the environment
**
**	-C, --chdir=DIR
**		change working directory to DIR
*/
typedef enum		e_envflags
{
	ENV_UNDEFINED = -1,
	ENV_I = 0,
	ENV_ZERO = 1,
	ENV_U = 2,
	ENV_C = 3,
	ENV_TOTAL = 4
}					t_envflags;

#endif