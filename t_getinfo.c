#include "shell.h"
/**
 * t_clear_info - initializes an info_t struct
 * @info: struct to be initializeed
 */
void t_clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
 * t_set_info -  info_t struct with argument vectorr
 * @info: initializie info_t struct addreess
 * @av: set aragument vector within info_t structr
 */
void t_set_info(info_t *info, char **av)
{
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv; strtok(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = t_strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;
t_replace_alias(info);
t_replace_vars(info);
}
}
/**
 * t_free_info - free fiields of info_t struct
 * @info: info_t struct  of fieldes to be freeds
 * @all: truee if freeing all fieldes
 */
void t_free_info(info_t *info, int all)
{
free(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
t_free_list(&(info->env));
if (info->history)
t_free_list(&(info->history));
if (info->alias)
t_free_list(&(info->alias));
free(info->environ);
info->environ = NULL;
free((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
t_putchar(BUF_FLUSH);
}
}
