#include "main.h"
/**
 * times_table - print every time table from 0 to 9
 */
void times_table(void)
{
int i;
int result;
for (i = 0; i <= 9; i++)
{
int j;
for (j = 0; j <= 9; j++)
{
result = i * j;
if (result < 10)
{
_putchar(result + '0');
}
else
{
_putchar(result / 10 + '0');
_putchar(result % 10 + '0');
}
if (j != 9)
{
_putchar(',');
}
_putchar(' ');
}
_putchar('\n');
}
}