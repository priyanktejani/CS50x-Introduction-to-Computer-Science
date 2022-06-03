#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    long ccnum;
    int ccnumlen = 0, digits_sum = 0;

    do
    {
        // Prompts user for a credit card number
        printf("Number:");
        scanf("%ld", &ccnum);
    }
    while (ccnum < 0);

    // Iterate odd and even digits by Luhan's algorithm
    long odd_or_even = ccnum;
    while (odd_or_even > 0)
    {
        // determine even digit
        if (ccnumlen % 2 == 0)
        {
            digits_sum += (odd_or_even % 10);
        }
        else
        {
            // multiply odd digit by 2
            int odd_digit = 2 * (odd_or_even % 10);

            // If the odd digit falls into two units, separate it and add it up
            digits_sum += (odd_digit / 10) + (odd_digit % 10);
        }
        odd_or_even /= 10;
        ccnumlen++;
    }

    // Iterate the first two digits of the credit card
    for (int i = 2; i < ccnumlen; i++)
    {
        ccnum /= 10;
    }

    // Check if the credit card is valid and its type
    bool isvalid =  digits_sum % 10 == 0;
    if (isvalid && (ccnum == 34 || ccnum == 37) && ccnumlen == 15)
    {
        printf("AMEX\n");
    }
    else if (isvalid && (ccnum >= 51 && ccnum <= 55) && ccnumlen == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (isvalid && (ccnum >= 40 && ccnum <= 49) && (ccnumlen == 13 || ccnumlen == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}