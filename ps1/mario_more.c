#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for height between 1 and 8
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    // loop though the lines & print chars accordingly
    for (int i = 0; i < h; i++)
    {

        // print left spaces
        for (int j = 0; j < (h - i - 1); j++)
        {
            printf(" ");
        }

        // print left hashes
        for (int k = 0; k < (i + 1) ; k++)
        {
            printf("#");
        }

        // print 2 empty spaces
        printf("  ");

        // print right hashes
        for (int k = 0; k < (i + 1) ; k++)
        {
            printf("#");
        }

        // print a new line
        printf("\n");
    }
}
