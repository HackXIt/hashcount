#include <stdio.h>
#include <stdlib.h>

/*
 *  An example of how to use strtol() to read a number
 *  and validate that one was entered correctly.
 *
 */

int main(void)
{
    char buf[BUFSIZ];
    char *p;
    long int i;
    while (buf[0] != 'c')
    {
        printf("Enter a number: ");
        if (fgets(buf, sizeof(buf), stdin) != NULL)
        {
            i = strtol(buf, &p, 10);
            if (buf[0] != '\n' && (*p == '\n' || *p == '\0'))
                printf("Valid number of %ld entered\n", i);
            else if (buf[0] == 'c' || (*p == 'c'))
            {
                printf("You've entered an exit character.");
                break;
            }
            else
            {
                printf("The number was %ld, followed by %s\n", i, p);
            }
        }
    }
    return (0);
}

/*
 * Program output:
   Enter a number: 123abc
   The number was 123, followed by abc
 *
 */