#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get the credit card in the correct format
    long cc_num;
    do
    {
        cc_num = get_long("Number: ");
    }
    while (cc_num < 0);

    // declear sum that doesn't needed to be multiplied by 2
    // and the once that does
    int x1sum = 0, x2sum = 0;

    // get the sum of every other digit from the last digit
    // by getting the modulus of cc_num, divide it by 100
    // and loop through it until it is 0
    // the remaining number is represented by "i"
    for (long i = cc_num; i > 0; i /= 100)
    {
        x1sum += i % 10;
    }

    // same as above but sum is multiplied by 2
    // "i" is divided by 10 to start from the second to last
    // digit; if statement for the products
    for (long i = cc_num / 10; i > 0; i /= 100)
    {
        if (((i % 10) * 2) > 9)
        {
            x2sum += ((i % 10) * 2) / 10;
            x2sum += ((i % 10) * 2) % 10;
        }
        else
        {
            x2sum += ((i % 10) * 2) % 10;
        }
    }

    // add sums together
    int checksum = x1sum + x2sum;

    // check card validity
    if (checksum % 10 == 0)
    {
        if ((cc_num >= 340000000000000 && cc_num < 350000000000000) || (cc_num >= 370000000000000 && cc_num < 380000000000000))
        {
            printf("AMEX\n");
        }
        else if (cc_num >= 5100000000000000 && cc_num < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else if ((cc_num >= 4000000000000 && cc_num < 5000000000000) || (cc_num >= 4000000000000000 && cc_num < 5000000000000000))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
