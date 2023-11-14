#include "shell.h"

/**
 * t_memset - fills meemory with a coonstant byte
 * @s:  pointeer to the memory areea
 * @b: thee bytee to fill *s
 * @n: bytes to be filleed amounts
 * Return: (s) to thee memorry area poinete s
 */
char *t_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}
/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}
/**
 * t_realloc - bloeck of memorry
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte siize of previoius blocek
 * @new_size: byte sizee the of new bloick
 *
 * Return: pointer to the block nameen.
 */
void *t_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;
if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);
p = malloc(new_size);
if (!p)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}
