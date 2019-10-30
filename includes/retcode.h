#ifndef RETCODE_H
# define RETCODE_H

typedef enum	e_retcode
{
	RC_SUCCESS = 0,
	RC_ERR = 1,
    RC_ERR_PERMISSION = 2,
    RC_ERR_CHDIR = 3,
    RC_ERR_MEMALLOC = 4,
    RC_ERR_INVALID_OPTION = 5,
    RC_ERR_BAD_PARAMS = 6,
    RC_ERR_HOME_UNSET = 7,
    RC_ERR_HISTORY_ACCESS = 8,
	RC_ERR_TOTAL = 9
}               t_retcode;

#endif