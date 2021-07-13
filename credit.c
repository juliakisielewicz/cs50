#include <cs50.h>
#include <math.h>
#include <stdio.h>



int main(void)
{
    
    long number = get_long("Number: ");
    
    long n = number;
    int sum1 = 0, sum2 = 0;
    int count = 0;
    int tmp;
    while (n != 0)
    {
        if(count % 2 == 0)
            sum1 = sum1 + (n % 10);
        else
        {
            tmp = 2 * (n % 10);
            if ( tmp > 9 )
                sum2 = sum2 + (tmp % 10) + (tmp / 10);
            else
                sum2 = sum2 + tmp;
        }
        
        n = n / 10;
        count++;
    }
    
    int checksum = sum1 + sum2;
    printf("checksum: %i\n", checksum);
    printf("number od digits: %i\n", count);

    if(checksum % 10 == 0)
    {
        if (count == 15 && ((number / (long) pow(10,13)) == 34 ||  (number / (long) pow(10,13)) == 37)) 
            printf("AMEX\n");
        else if (count == 16 && (number / (long) pow(10,14) == 51 || number / (long) pow(10,14) == 52 ||number / (long) pow(10,14) == 53 ||number / (long) pow(10,14) == 54 ||number / (long) pow(10,14) == 55)) 
            printf("MASTERCARD\n");
        else if ((count == 13 && number / (long) pow(10,12) == 4) || (count == 16 && number / (long) pow(10,15) == 4))
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
}