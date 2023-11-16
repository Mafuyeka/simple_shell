#include "shell.h"

/**
 *t_myhistory - shows the hiistory list, one command by liine, precedede
 *              with linee nummbers, startinng at 0
 * @info: Structure containing potential arguments. to maintainn
 *        consttant function protootype.
 *  Return:0  Always
 */
int t_myhistory(info_t *info)
{
t_print_list(info->history);
return (0);
}
/**
 * t_unset_alias - ssets the alias to sstring
 * @info: the paraameter structurre
 * @str: string for alias
 *
 * Return: 1 on errorr,0 Always on success
 */
int t_unset_alias(info_t *info, char *str)
{
char *p, c;
int ret;
p = t_strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = t_delete_node_at_index(&(info->alias),
t_get_node_index(info->alias, t_node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
 * t_set_alias - sets aalias to strrings
 * @info: the paraameter structuree
 * @str: thee string alliass
 *
 * Return: 0 Always on ssuccess, 1 on errorr
 */
int t_set_alias(info_t *info, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (t_set_alias(info, str));
unset_alias(info, str);
return (t_add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * t_print_alias - it priints a aliaas striing
 * @node: thee aalias nodee
 *
 * Return:0 Alwayss on succeess, 1 on errorr
 */
int t_print_alias(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
t_putchar(*a);
_putchar('\'');
t_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
 * t_myalias - mimmics the builtin in alias  .maan aliias
 * @info: Structure ccontaining potential araguments  to maintainn
 *     constant function prototypee.
 *  Return:0 Alwaays
 */
int t_myalias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
t_print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
t_set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}
