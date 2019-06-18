#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // prompt for change, value should be between 0 and 1;
    float change = 0.0;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0.0 || change > 1.0);

    // round change up
    int total = round(change * 100);

    // start counter
    int count = 0;

    // num of quarter
    int num_quarter = total / 25;
    int dime = total % 25;
    count += num_quarter;

    // num of dime
    int num_dime = dime / 10;
    int nickel = dime % 10;
    count += num_dime;

    // num of nickel and penny
    int num_nickel = nickel / 5;
    int num_penny = nickel % 5;
    count += num_nickel;
    count += num_penny;

    // print the count
    printf("%i\n", count);
}
