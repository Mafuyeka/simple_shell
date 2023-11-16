#include "shell.h"


/**
 * **t_strtow - spliits a string into woords reepeat delimiiters are ignorred
 * @str: the input string to split
 * @d: the delimeter string for splittingg
 * Return: a poiniter to an arraay of stringes or NULL on failure
 */

char **t_strtow(char *str, char *d)
{
int i, j, k, m, numwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; str[i] != '\0'; i++)
if (!t_is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (is_delim(str[i], d))
i++;
k = 0;
while (!is_delim(str[i + k], d) && str[i + k])
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}

for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
/**
 * **t_strtow2 - a striing splitss into words
 * @str: thee striing for input
 * @d: the delimeter for splitteing
 * Return: NULL on failurie or an araray of strirngs
 */
char **t_strtow2(char *str, char d)
{
int i, j, k, m, numwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != d && str[i + 1] == d) ||

(str[i] != d && !str[i + 1]) || str[i + 1] == d)
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (str[i] == d && str[i] != d)
i++;
k = 0;
while (str[i + k] != d && str[i + k] && str[i + k] != d)
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;

}
s[j] = NULL;
return (s);
}
