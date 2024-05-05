#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VAT 18 / 100
#define STU 122 / 1000
#define OVR 10 / 100
int calculation(int product, int service, int satirsayisi)
{
    float price = 0;
    float totalprice = 0;
    int counter = 0;

    FILE *ptr;
    ptr = fopen("menu.txt", "r");
    char deneme;

    if (ptr == NULL)
    {
        printf("ERROR\n");
        return 0;
    }

    for (int i = 0; i < product; i++) // in which row has the meal we choose this loop finds that row
    {
        while (getc(ptr) != '\n')
            ;
    }
    FILE *pr;

    pr = fopen("receipt.txt", "a+");

    if (service != 0)
    {
        fprintf(pr, "%d*", service); // how many services are printing in the receip.txt
        while (fscanf(ptr, "%c", &deneme) == 1 && deneme != ' ')
        {
            fprintf(pr, "%c", deneme); // printing meal name in to the receip.txt
            counter++;
        }
    }
    while (getc(ptr) != ' ')
        ;
    fscanf(ptr, "%f", &price); // taking meals price

    totalprice += price * service; // calculating that meals total price against the services

    if (service != 0)
    {
        if (counter >= 6)
            fprintf(pr, "\t\t          %.2f\n", totalprice); // printing meals price to the receip.txt
        else
            fprintf(pr, "\t\t\t          %.2f\n", totalprice); // printing meals price to the receip.txt
    }
    // printf("\nprice %.2f\n", totalprice);

    fclose(ptr);
    fclose(pr);
    return totalprice;
}

int choice(int satirsayisi)
{
    int service = 1;
    int product = 0;
    float totalprice = 0;
    float stu_disc = 0, ovr_hundred = 0, vat_price = 0;
    char student;
    char a;

    while (service != 0) // just for entering 0 for service programme dones
    {
        printf("Please choose a product (1-8):");
        scanf("%d", &product);
        printf("How many servings do you want?:");
        scanf("%d", &service);
        totalprice += calculation(product, service, satirsayisi); // in evey loop calculation function find the meal name and the price for against the service
    }

    FILE *pr;

    pr = fopen("receipt.txt", "a+");

    while ((a = getchar()) && a != '\n') // to clean buffer
        ;
    printf("Are you student (Y/N):");
    scanf("%c", &student);
    printf("\n");
    switch (student)
    {
    case 'Y':
        stu_disc = totalprice * STU;

        fprintf(pr, "Total\t\t\t          %.2f\n", totalprice);
        fprintf(pr, "Student price\t\t\t  -%.2f\n\n", stu_disc);
        fprintf(pr, "-----------------------------------------\n\n");
        fprintf(pr, "Price\t\t\t          %.2f\n", (totalprice - stu_disc));
        fprintf(pr, "Price + VAT\t\t\t  %.2f\n", (totalprice - stu_disc) + ((totalprice - stu_disc) * VAT));
        fclose(pr);
        break;
    case 'N':

        ovr_hundred = totalprice * OVR;
        fprintf(pr, "Total\t\t\t          %.2f\n", totalprice);
        if (totalprice >= 150)
            fprintf(pr, "Over 150 Tl\t\t\t -%.2f\n\n", ovr_hundred);
        fprintf(pr, "-----------------------------------------\n\n");
        fprintf(pr, "Price\t\t\t          %.2f\n", (totalprice - ovr_hundred));
        fprintf(pr, "Price + VAT\t\t\t  %.2f\n", (totalprice - ovr_hundred) + ((totalprice - ovr_hundred) * VAT));
        fclose(pr);
        break;

    default:
        printf("Please enter a valid answer\n");
        break;
    }

    pr = fopen("receipt.txt", "r"); // for print the receipt in to the terminal

    while ((a = getc(pr)) != EOF)
    {

        printf("%c", a);
    }
    printf("\n");
    fclose(pr);

    return 0;
}

int menu()
{
    char deneme;
    int satirsayisi = 0;
    FILE *ptr;
    ptr = fopen("menu.txt", "r");

    if (ptr == NULL)
    {
        printf("ERROR\n");
        return 0;
    }
    // while(!feof(ptr))
    // {
    //     fgetc(ptr);
    // }
    while (getc(ptr) != '\n')
        ;
    printf("Product\n");
    while ((deneme = getc(ptr)) != EOF) // to not printing first row products and price
    {

        if (deneme != '.' && !('0' <= deneme && deneme <= '9')) // just for printing menu without prices
            printf("%c", deneme);

        if (deneme == '\n') // finding row number to choose which meal we buy
            satirsayisi++;
    }
    printf("\n");
    // printf("%d\n", satirsayisi);

    choice(satirsayisi);
    fclose(ptr);
}

void rps_game()
{
    char playAgain = 'Y';
    while (playAgain == 'Y')
    {
        printf("Please make a choice!\n1: Rock, 2: Paper, 3: Scissors\n");
        int userChoice;
        scanf("%d", &userChoice);
        while (userChoice < 1 || userChoice > 3)
        {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            scanf("%d", &userChoice);
        }

        srand(time(NULL)); // seed random number generator
        int computerChoice = rand() % 3 + 1;

        // printing choices
        switch (userChoice)
        {
        case 1:
            printf("You chose Rock. ");
            break;
        case 2:
            printf("You chose Paper. ");
            break;
        case 3:
            printf("You chose Scissors. ");
            break;
        }
        switch (computerChoice)
        {
        case 1:
            printf("I chose Rock. ");
            break;
        case 2:
            printf("I chose Paper. ");
            break;
        case 3:
            printf("I chose Scissors. ");
            break;
        }

        // comparing choices and print result
        if (userChoice == computerChoice)
            printf("It's a tie!\n");
        else if ((userChoice == 1 && computerChoice == 3) || (userChoice == 2 && computerChoice == 1) || (userChoice == 3 && computerChoice == 2))
            printf("You won!\n");
        else
            printf("I won!\n");

        // asking user to play again
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &playAgain);
    }
}

int main()
{
    int product = 0;
    int service = 1;
    char a;

    FILE *pr; // for receipt.txt

    pr = fopen("receipt.txt", "w");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char str[20];
    strftime(str, sizeof(str), "%d.%m.%Y/%H:%M", t); // for date
    fprintf(pr, "200104004031\t\t %s\n\n", str);
    fprintf(pr, "-----------------------------------------\n\n");
    fprintf(pr, "Product                         Price(TL)\n\n");
    fprintf(pr, "-----------------------------------------\n\n");
    fclose(pr);

    menu(); // this function provides the take menu from menu.txt

    rps_game(); // rock scissor paper game
}