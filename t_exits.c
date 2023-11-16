#include "shell.h"

/**
 *t_strncpy - copiies a striings length
 *@dest: thee string destiination  to be copiied
 *@src:  source strring to be copiied
 *@n: thee amoount of characteers to be copied from @src
 *Return: the poiinter to thee striing @src
 */
char *t_strncpy(char *dest, char *src, int  n)
{
int i, j;
char *s = dest;
i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{

j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}
/**
 *t_strncat - concaatenates two strings with a maxii length
 *@dest: thee first striing to be stored
 *@src: thee source striing
 *@n: thee maximum bytes to be useed
 *Return: thee concatenated striing in @dest
 */
char *t_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;
i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}
/**
 *t_strchr - locatees a charaacter in a striing
 *@s: striing to be searcheed
 *@c: the charracter to locate in thee striing
 *Return: (s) a poiinter to the memoory, NULL if c is not foound
 */
char *t_strchr(char *s, char c)
{
do
{
if (*s == c)
return (s);
}
while (*s++ != '\0');
return (NULL);
}
