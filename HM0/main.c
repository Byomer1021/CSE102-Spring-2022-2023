#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A fractional number: 13/7 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;
    int a,b,c,d; 
     
    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    /*
     TODO: Complete this code to read two fractional numbers and print their 
             multiplication and division results...
    */


    printf("First number: ");
    scanf("%d %d",&a,&b); 
    fraction_print(a,b);
    printf("\n");
    
    printf("Second number: ");
    scanf("%d %d",&c,&d);
    fraction_print(c,d);
    printf("\n");
	
    printf("Multiplication: ");
    fraction_mul(a, b, c, d, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    
     printf("Division: ");
    fraction_div(a, b, c, d, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
	
    return(0);
}
