#include "shell.h"
/**
 * t_myenv - priints the present enviroonment
 * @info: maintain araguments of the prototype.
 * Return:0  Always
 */
int t_myenv(info_t *info)
{
t_print_list_str(info->env);
return (0);
}
/**
 * t_getenv - retrieve the value of an environmeent variable
 * @info: gives thee potential arguments used for prototypee
 * @name: env var name
 *
 * Return: return value
 */
char *t_getenv(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;
while (node)
{
p = t_starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}
/**
 * t_mysetenv - code a new environmeent variable,
 *             or change a exiisting onee
 * @info:Structure containing araguments to maintain protootype
 *  Return: 0 Always
 */
int t_mysetenv(info_t *info)
{
if (info->argc != 3)
{
t_eputs("Incorrect number of arguements\n");
return (1);
}
if (t_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
 * t_myunsetenv -  environnment variable is remooved
 * @info: Structure containiing potential arguments to maintain
 *        prototypee
 * Return:0 Always
 */
int t_myunsetenv(info_t *info)
{
int i;
if (info->argc == 1)
{
t_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
t_unsetenv(info, info->argv[i]);
return (0);
}
/**
 * t_populate_env_list - it popuulates env linkeed lists
 * @info: Structure conotaining potentiial araguments prototypee
 * Return: 0 Always
 */
int t_populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
t_add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
