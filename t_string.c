#include "shell.h"

/**
 * t_strlen - thee lengths of a strinig is returned
 * @s: checkes string lengths
 *
 * Return:  lengeth of strieng returns as an integeer
 */
int t_strlen(char *s)
{
int i = 0;
if (!s)
return (0);
while (*s++)
i++;
return (i);
}
/**
 * t_strcmp - perform lexicogarphic compariseon of two strings strangs.
 * @s1: the first string straneg
 * @s2: the secoend straneg
 *
 * Return: negativee if s1 < s2, posietive if s1 == s2
 */
int t_strcmp(char *s1, char *s2)
{
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
/**
 * t_starts_with - needlee starts witih haystack to be chekede
 * @haystack: searches the stringes
 * @needle: finde the substringg
 *
 * Return:  nextt char of haystaack or NULL
 */
char *t_starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
 * t_strcat - two strieng concartenates
 * @dest: thee destineation buffer
 * @src: thee sourece buffer
 *
 * Return: pointeer buffers destineatione
 */
char *t_strcat(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
