#include <stdio.h>

void gcd_calculator (int x, int y)
{
    int i;
    int gcd = 0;

    printf("Please enter two integer: \n");
    scanf("%d %d", &x, &y);

    if (x < y) // to checking for loop minumum number
    {

        for (i = 1; i <= x; i++) // it is turning to min because higher is not needed
        {

            if (x % i == 0 && y % i == 0)
                gcd = i;
        }
    }
    else
    {
        for (i = 1; i <= y; i++) // it is turning to min because higher is not needed
        {
            if (x % i == 0 && y % i == 0)
                gcd = i;
        }
    }

    printf("%d ve %d GCD is : %d\n", x, y, gcd);
}

void sum_calc (int num1, int num2)
{
    int sum = 0;
    int num1_digit = 0, sum_digit = 0, num2_digit = 0; // if digit is 0 it means 0-9 if digit is 1 it means 10-99 if digit is 2 it means 100-999 if digit is 3 it means 1000-9999
    printf("Please enter two integer: \n");
    scanf("%d %d", &num1, &num2);
    sum = num1 + num2;

    // if (num1 / 10 < 1)
    //     num1_digit = 0;
    // else if (num1 / 10 >= 1 && num1 / 10 < 10)
    //     num1_digit = 1;
    // else if (num1 / 100 >= 1 && num1 / 100 < 10)
    //     num1_digit = 2;
    // else
    //     num1_digit = 3;
    // printf("%d :::::", num1_digit);
    //
    // if (num2 / 10 < 1)
    //    num1_digit = 0;
    // else if (num2 / 10 >= 1 && num2 / 10 < 10)
    //    num2_digit = 1;
    // else if (num2 / 100 >= 1 && num2 / 100 < 10)
    //    num2_digit = 2;
    //
    // else
    //    num2_digit = 3;
    //
    // printf("\t%d :::::", num2_digit);
    //
    // if (sum / 10 < 1)
    //    sum_digit = 0;
    // else if (sum / 10 >= 1 && sum / 10 < 10)
    //    sum_digit = 1;
    // else if (sum / 100 >= 1 && sum / 100 < 10)
    //    sum_digit = 2;
    // else
    //    sum_digit = 3;
    //
    // printf("\t %d :::::\n\n", sum_digit);

    printf("First number\t: %d\n", num1);
    printf("Second number\t: %d\n", num2);
    printf("Rwsult:\n");

    // if (num1_digit == 0 )
    //     printf("\t%7d\n", num1);
    // else if (num1_digit == 1)
    //     printf("\t%7d\n", num1);
    // else if (num1_digit == 2)
    //     printf("\t%7d\n", num1);
    // else if (num1_digit == 3 )
    printf("\t%7d\n", num1); // Since it will be one after the other until the last digit in the collection process, I reserved a place for 7 units.

    // if (num2_digit == 0)
    //     printf("\t%7d\n", num2);
    // else if (num2_digit == 1)
    //     printf("\t%7d\n", num2);
    // else if (num2_digit == 2)
    //     printf("\t%7d\n", num2);
    // else if (num2_digit == 3)
    printf("\t%7d\n", num2); // Since it will be one after the other until the last digit in the collection process, I reserved a place for 7 units.

    printf("\t+\n");
    printf("\t-------\n");

    // if (sum_digit == 0)
    //     printf("\t7%d\n", sum);
    // else if (sum_digit == 1)
    //     printf("\t%7d\n", sum);
    // else if (sum_digit == 2)
    //     printf("\t%7d\n", sum);
    // else if (sum_digit == 3)
    printf("\t%7d\n", sum); // Since it will be one after the other until the last digit in the collection process, I reserved a place for 7 units.
}

void multip_calc (int num1, int num2)
{
    int multip = 0;
    int multip_digit = 0;
    int kat1 = 0, kat2 = 0;
    int kat3 = 0, kat4 = 0; // only necesseray for 3 digits
    printf("Please enter two integer: \n");
    scanf("%d %d", &num1, &num2);
    multip = num1 * num2;
    kat1 = num1 * (num2 % 10);           // First stage of multiplication  number2's last digit multiplicate with number1
    kat2 = (num1 * (num2 % 100)) - kat1; // Second stage of multiplication number2's last two digits multiplicate with number1 than first stage subtract from this
    kat3 = num1 * num2 - (kat1 + kat2);  // Third stage of multiplication if number2 has 3 digits multiplicate the 2 numbers than subtract stage 1 and 2

    printf("First number\t: %d\n", num1);
    printf("Second number\t: %d\n", num2);
    printf("Result: \n");
    printf("\t%7d\n", num1);
    printf("\t%7d\n", num2);
    printf("\t*\n");
    printf("\t-------\n");
    printf("\t%7d\n", kat1);           // in multiplication in every digits slide one left at start ı gave 7 digits for first stage
    printf("\t%6d\n", kat2 / 10);      // then ı dropped one because sliding and divide to ten because of the digit (to get rid of 0)
    if (num2 >= 100)                   // if num2 has 3 digit then there should be one more stage
        printf("\t%5d\n", kat3 / 100); // and ı dropped 1 again because sliding and divide to 100 because of digit rule (to get rid of 0)
    printf("\t+\n");
    printf("\t-------\n");
    printf("\t%7d\n", multip);
    //}
}

int greater_or_lesser_5 ()
{
    int num;

    printf("Please enter an integer between 1 and 10: ");
    scanf("%d", &num);

    if (num < 1 || num > 10) // if number is not in the range of 1 to 10 program terminates
    {
        printf("Invalid input\n");
        return 0;
    }
    else if (num > 5)
    {
        printf("The integer you entered is greater than 5\n");
    }
    else
    {
        printf("The integer you entered is less than or equal to 5\n");
    }
}