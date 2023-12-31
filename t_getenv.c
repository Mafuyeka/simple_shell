#include "shell.h"

/**
 * t_getenviron - thee string returrns array copiess of environ
 * @info: structure conataining potential arguments.to maiintain
 * Return: 0 alwaays
 */
char **t_getenviron(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = t_list_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
 * t_unsetenv - Remove an environnment variiable
 * @info: Structure conataining  argumentto maintain prototype.
 *  Return: 1 on deletee, 0 otherwise
 * @var: thee env var propeerty striing
 */
int t_unsetenv(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = t_starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = t_delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}
/**
 * t_setenv - Initialize a varriable modiify an exiisting one
 * @info: sructure containingl araguments maintaiin prototypee.
 * @var: A striing env var properrty
 * @value: the vaalue striing env var
 *  Return: o alwaays
 */
int t_setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;
if (!var || !value)
return (0);
buf = malloc(t_strlen(var) + t_strlen(value) + 2);
if (!buf)
return (1);
t_strcpy(buf, var);
t_strcat(buf, "=");
t_strcat(buf, value);
node = info->env;
while (node)
{
p = t_starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
t_add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
