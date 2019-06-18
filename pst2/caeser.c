#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // If the wrong format is entered
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Get the plaintext
    string s = get_string("plaintext:  ");

    // Store value of argv[1] in key
    int key = atoi(argv[1]);

    // Print ciphertext
    printf("ciphertext: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // For lowercase char
        if (islower(s[i]))
        {
            printf("%c", (s[i] - 'a' + key) % 26 + 'a');
        }

        // For uppercase char
        else if (isupper(s[i]))
        {
            printf("%c", (s[i] - 'A' + key) % 26 + 'A');
        }

        // For non alphabets
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}
