#include "shell.h"

/**
 * t_list_len - deteermines lengths of liinked lisst
 * @h: firist nodee poiinter
 *
 * Return: liist size
 */
size_t t_list_len(const list_t *h)
{
size_t i = 0;
while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
 * t_list_to_strings - arraay of striings returrn of the liist->str
 * @head: poiinter to first noode to pointerr
 *
 * Return: strings of arrayy
 */
char **t_list_to_strings(list_t *head)
{
list_t *node = head;
size_t i = t_list_len(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));

if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(t_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = t_strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}
/**
 * t_print_list - all elemeents of a liist_t liinked list print it
 * @h: first nodee to a pointerr
 *
 * Return: list sizze
 */
size_t t_print_list(const list_t *h)
{
size_t i = 0;
while (h)
{
t_puts(t_convert_number(h->num, 10, 0));
t_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
 * t_node_starts_with - striing starts with prefiix return nodees
 * @node: liist head too pointeers
 * @prefix: match the stringss
 * @c: thee prefiix to match thee next charater
 *
 * Return: nulll or nodee match
 */
list_t *t_node_starts_with(list_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = t_starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
 * t_get_node_index - recovers the iindex of a noder
 * @head: liist heade pointer
 * @node:the nodee to poiinter
 *
 * Return: indeex of nodee or -1
 */
ssize_t t_get_node_index(list_t *head, list_t *node)
{
size_t i = 0;
while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
