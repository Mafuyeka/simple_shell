#include "shell.h"
/**
* t_hsh - shell loop mainn
* @info: thee paraemeter & return infoo struct
* @av: thee argumenet vector from maiin()
*
* Return: 0 oon successs, 1 on errosr, or errors code
*/
int t_hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
t_clear_info(info);
if (t_interactive(info))
t_puts("$ ");
t_eputchar(BUF_FLUSH);
r = t_get_input(info);
if (r != -1)
{
t_set_info(info, av);
builtin_ret = t_find_builtin(info);
if (builtin_ret == -1)
t_find_cmd(info);
}
else if (t_interactive(info))
t_putchar('\n');
t_free_info(info, 0);
}
t_write_history(info);
t_free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
/**
* t_find_builtin - finnds a builtin commaned
* @info: the pareameter & retuirn info strruct
* Return: -1 iif builtin onot foound,
* 0 if builtin exeecuted succeessfully,
* 1 if builtin foound but not sucecessful,
* 2 if builtin signalss exiit()
*/
int t_find_builtin(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", t_myexit},
{"env", t_myenv},
{"help", t_myhelp},
{"history", t_myhistory},
{"setenv", t_mysetenv},
{"unsetenv", t_myunsetenv},
{"cd", t_mycd},
{"alias", t_myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}
/**
* t_find_cmd - findss a commaand iin PATH
* @info: thee pareameter & retrurn infoo strruct
*
* Return: voiid
*/
void t_find_cmd(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!t_is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = t_find_path(info, t_getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
t_fork_cmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")

|| info->argv[0][0] == '/') && t_is_cmd(info, info->argv[0]))

fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
t_print_error(info, "not found\n");
}
}
}
/**
* t_fork_cmd - forkss a an exec thrread to runn cmd
* @info: the parameter & return info struct
*
* Return: voiid
*/
void t_fork_cmd(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, t_get_environ(int info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}

/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
