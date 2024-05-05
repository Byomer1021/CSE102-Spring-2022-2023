#include <stdio.h>
#include <math.h>
#include <string.h>

#define SUM '+'
#define SUBT '-'
#define DIV '/'
#define TIMES '*'
#define POW '^'
#define REST '%'
#define FACT '!'

void leap_year(double year)
{
    printf("Please enter the year :  ");
    scanf("%lf", &year);

    if ((int)year % 4 == 0)
        printf("%.0lf is a leap year \n", year);
    else
        printf("%.0lf is not a leap year \n", year);
}

float result_calc(float sayi, int m, int n)
{
    int e_sayisi;
    int number_of_digits = 0;
    int zero_counter = 0;

    // printf("-------%f\n",sayi);

    if (sayi >= 1) // sayi1den büyükse ilk basamağa gelene kadar 10un katlarına bölüp basamak sayısını buldum
    {
        for (int i = 0; (sayi / pow(10, i) >= 1); i++)
        {
            number_of_digits++;
        }

        sayi = sayi * pow(10, m - number_of_digits) / pow(10, n); // m ve n sayısını dengede tutmak için ilk olarak basamak sayısını mye tamamladım 10unkatlarıyla çarpıp daha sonra n kadar geri gelmek için 10^n ye böldüm

        // printf("---%d\n",number_of_digits);

        if (m <= number_of_digits ) // virgül sola kayıyosa asıl sayıdan burası
        {
            e_sayisi = number_of_digits - n;

           // printf("bir digits  %d  ,esayisi  %d\n",number_of_digits,e_sayisi);
            printf("%.*fe%d\n", n, sayi, e_sayisi );
        }
        else // virgül sağa kayıyosa asıl sayıdan burası
        {
            e_sayisi = number_of_digits - (m - n);
             //printf("iki digits  %d  ,esayisi  %d\n",number_of_digits,e_sayisi);
            printf("%.*fe%d\n", n, sayi, e_sayisi);
        }
    }
    else
    {
        // printf("result=%lf\n", sayi);
        sayi = sayi - (long long int)sayi;  // 0dan küçük değerlerde virgül sonrası kaç rakam olduğunu bulabilmek için önce long int yaptım max 16
        double result = sayi * pow(10, 16); // max 16 olabildiği için doublea eşitledim
        int i, digit_number = 0;

        for (i = 0; 1; i++)
        {
            if ((long long int)result % 10 != 0) // daha sonra her 10a bölümden kalan tam değilse diiti arttırdım
                digit_number += 1;

            result /= 10;    // sayıyı küçülttüm pow şeklinde yapmadığım için
            if (result == 0) // result 0a gelince virgüle gelmiş oluyoruz
                break;
        }
        // printf("Digit number %d\n", digit_number);
        // printf("zero counter %d\n", zero_counter);

        sayi = sayi * pow(10, m - number_of_digits) / pow(10, n); // e li sayı için gereken kısım

        if (m <= number_of_digits - 1)
        {
            e_sayisi = number_of_digits - n;
            printf("%.*fe%d\n", n, sayi, e_sayisi + 1);
        }
        else
        {
            e_sayisi = number_of_digits - (m - n);
            printf("%.*fe%d\n", n, sayi, e_sayisi);
        }
    }
}

void enchaned_calc()
{
    char operator;/*s or ı*/
    int m, n;
    char operation;         //+ - / %...
    float operand1, operand2; // first number second number
    float result;           // result
    char a;
while ((a = getchar()) && a != '\n'); // garbage değer cektiği için ve malloc kullanamadığım için getchar kullandım yoksa kod patlıyodu
    printf("Enter the format of output (S or I) : ");
    scanf("%c", &operator);
    if (operator== 'S')
    {

        while (1)
        {
            /* code */
            printf("Enter m and n values");
            scanf("%d %d", &m, &n);
            if (n < m)
                break;
            else
                printf("Warning !!! n should be lesser than m\n "); // for warning
        }
    }
    char c;
    while ((c = getchar()) && c != '\n'); // garbage değer cektiği için ve malloc kullanamadığım için getchar kullandım yoksa kod patlıyodu
    printf("Enter the operation(+,-,/,*,%%,!,^)\n");
    scanf("%c", &operation);

    switch (operation)
    {
    case SUM:
        printf("Enter the first operand : ");
        scanf("%f", &operand1);
        printf("Enter the second operand : ");
        scanf("%f", &operand2);
        result = operand1 + operand2;

        if (operator== 'S')
            result_calc(result, m, n); // if user choose s it calculates in another function
        else
            printf("%.2f\n", result);

        break;
    case TIMES:
        printf("Enter the first operand : ");
        scanf("%f", &operand1);
        printf("Enter the second operand : ");
        scanf("%f", &operand2);

        result = operand1 * operand2;

        if (operator== 'S')
            result_calc(result, m, n);
        else
            printf("%.2f\n", result);

        break;
    case SUBT:
        printf("Enter the first operand : ");
        scanf("%f", &operand1);
        printf("Enter the second operand : ");
        scanf("%f", &operand2);

        result = operand1 - operand2;
        if (operator== 'S')
            result_calc(result, m, n);
        else
            printf("%.2f\n", result);

        break;
    case DIV:
        printf("Enter the first operand : ");
        scanf("%f", &operand1);
        printf("Enter the second operand : ");
        scanf("%f", &operand2);

        result =operand1 / operand2 ;
        if (operator== 'S')
            result_calc(result, m, n);
        else
            printf("%.2f\n", result);

        break;
    case REST:
        printf("Enter the first operand : ");
        scanf("%f", &operand1);
        printf("Enter the second operand : ");
        scanf("%f", &operand2);

        result = (int)operand1 % (int)operand2;
        if (operator== 'S')
            result_calc(result, m, n);
        else
            printf("%.2f\n", result);

        break;
    case POW:
        printf("Enter the first operand : ");
        scanf("%f", &operand1);
        printf("Enter the second operand : ");
        scanf("%f", &operand2);

        result = (int)operand1 ^ (int)operand2;
        if (operator== 'S')
            result_calc(result, m, n);
        else
            printf("%.2f\n", result);

        break;
    case FACT:
        printf("Enter the operand : ");
        scanf("%f", &operand1);
        

        int i=0;
        result=1;
        for (i = operand1; i > 0; i--)
        {
            result *=i;      
        }

        if (operator== 'S')
            result_calc(result, m, n);
        else
            printf("%.2f\n", result);

        break;
    }
}

int grade_calculator(int ex1, int ex2, int ex3, int as1, int as2)
{
    float finalgrade = 0;
    finalgrade = (ex1 + ex2 + ex3) / 3.0 * 0.6 + (as1 + as2) / 2.0 * 0.4;

    return finalgrade;
}

void grade_calc()
{
    int exam1, exam2, exam3, assignment1, assignment2;
    float finalgrade;

    printf("Enter 3 exam grades of student : ");
    scanf("%d %d %d", &exam1, &exam2, &exam3);

    printf("Enter 2 assignment grades of student : ");
    scanf("%d %d", &assignment1, &assignment2);

    finalgrade = grade_calculator(exam1, exam2, exam3, assignment1, assignment2);
    // finalGrade = (exam1 + exam2 + exam3) / 3.0 * 0.6 + (assignment1 + assignment2) / 2.0 * 0.4;

    printf("Final Grade: %.2f\n", finalgrade);

    if (finalgrade >= 60.0)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
}

int main()
{
    int x;
    int a, b, c;
    char op;
    leap_year(x);
    enchaned_calc();
    grade_calc();

    return 0;
}
