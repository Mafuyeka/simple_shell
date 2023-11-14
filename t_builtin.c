#include "shell.h"
/**
* t_myexit -t_myexit is used to exit the shell
* @info:   the structure representing arguments
* Return: termination the exit status
* (0) if strcmp(info->argv[0], "exit") != "0"
*/
int t_myexit(info_t *info)
{
int exitcheck;
if (info->argv[1])
{
exitcheck = t_erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
t_print_error(info, "ilegal number: ");
t_puts(info->argv[1]);
t_putchar('\n');
return (1);
}
info->err_num = t_erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
 * t_mycd - changes currentt directtory of the process
 * @info: Structure ccontaining potential araguments. to maintain
 * constant function prototypee.
 * Return: Always 0
 */
int t_mycd(info_t *info)
{
char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		t_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = t_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = t_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (t_strcmp(info->argv[1], "-") == 0)
	{
		if (!t_getenv(info, "OLDPWD="))
		{
			t_puts(s);
			t_putchar('\n');
			return (1);
		}
		t_puts(t_getenv(info, "OLDPWD=")), t_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = t_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		t_print_error(info, "can't cd to ");
		t_eputs(info->argv[1]), t_eputchar('\n');
	}
	else
	{
		t_setenv(info, "OLDPWD", t_getenv(info, "PWD="));
		t_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * t_myhelp - changes current dir of the process
 * @info: the structure representing args prototype
 * Return: Always 0
 */
int t_myhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
t_puts("help call works. Function not yet implemented \n");
if (0)
t_puts(*arg_array); /* temp att_unused workaround */
return (0);
}
