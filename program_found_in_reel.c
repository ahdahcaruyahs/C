/*
Author: Shaurya Chadha
Date: 10/8/2024
Notes: Fixed in the sense removed conio.h and functions using those due to lack of people using turbo c.
Context: I found this code in a reel while i was watching. I will provide the original code in a comment below. Copy the  big comment below to copy original code.
Original Author for this program is currently unknown.
                                                                                                               |
                                                                                                               |
                                                                                                               |
                                                                                                               |
                                                                                                               \/
*/

#include<stdio.h>
//#include<conio.h>

void main()
{
    int a, b;

    //clrscr();  // Removed as it is part of conio.h which is not widely used anymore
    printf("Enter 2 numbers: ");
    scanf("%d %d", &a, &b);

    if (a == b)
        printf("Equal");
    else
        printf("Not Equal");

    //getch();  // Removed since getch() is from conio.h
    getchar();  // Used to pause the console until input is received
}

/*
#include<stdio.h>
#include<conio.h>

void main()
{
    int a, b;

    clrscr();
    printf("Enter 2 numbers: ");
    scanf("%d %d", &a, &b);

    if (a == b)
        printf("Equal");
    else
        printf("Not Equal");

    getch();
}
*/
