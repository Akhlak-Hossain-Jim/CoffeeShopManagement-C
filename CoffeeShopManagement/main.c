#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct menu
{
    int code;
    char name[40];
    double price;
    int inStock;
};
struct sold
{
    int code;
    char name[40];
    double price;
    int quantity;
};

int menuLength = 8;
int soldLength = 0;

struct menu COFFEEs[20] = {
    {101, "Americano  ", 120.4, 23},
    {102, "Cappuccino ", 100.4, 30},
    {103, "Espresso   ", 110.4, 20},
    {104, "Macchiato  ", 101.4, 33},
    {105, "Mocaccino  ", 130, 55},
    {106, "Latte      ", 135, 20},
    {107, "Cold Coffee", 103, 30},
    {108, "Affogato   ", 150, 10},
};

struct sold sellData[100];

void info()
{
    printf("Loading................\n\n\n\n");
    printf("\t\tWELCOME to COFFEE SHOP MANAGEMENT APP\n");
    printf("\n%c\t\t\tCreated by\n\n", ' ');
    printf("%c\t\tName:\tAklhak Hossain\t\tId:\t2022-3-60-057\n", ' ');
    printf("%c\t\tName:\tSaba Tasnim Khan\tId:\t2022-3-60-049\n", ' ');
    printf("%c\t\tName:\tHasnay Hasin\t\tId:\t2022-3-60-038\n", ' ');
    printf("%c\t\tName:\tAnika Tahseen\t\tId:\t2022-3-60-037\n", ' ');
    return;
}

void selectBasicOptionInfo()
{
    printf("\n\n\n \t\tSelect an Option:\n");
    printf("%c\t\t\t1. Print Item list.\n", ' ');
    printf("%c\t\t\t2. Add item to the menu.\n", ' ');
    printf("%c\t\t\t3. Delete item from the menu.\n", ' ');
    printf("%c\t\t\t4. Update quantity of an item.\n", ' ');
    printf("%c\t\t\t5. View todays stat.\n", ' ');
    printf("%c\t\t\t9. Exit\n", ' ');
    return;
}

void printList()
{
    printf("\n\n");
    printf("\t\t-------------------------------------------------\n\t\t| ID  | Name \t\t| Price \t| Available |\n \t\t-------------------------------------------------\n");
    for (int i = 0; i < menuLength; i++)
    {
        printf("\t\t| %d | %s\t| %.2lf\t| %d \t\t|\n", COFFEEs[i].code, COFFEEs[i].name, COFFEEs[i].price, COFFEEs[i].inStock);
        printf(" \t\t-------------------------------------------------\n");
    }
    return;
}

void printStat(int *ind)
{
    double sum = 0;
    if (soldLength > 0)
    {
        printf("\n\n");
        printf("\t\t-------------------------------------------------\n\t\t| ID  | Name \t\t| Quantity \t| Amount |\n \t\t-------------------------------------------------\n");
        for (int i = 0; i < soldLength; i++)
        {
            printf("\t\t| %d | %s\t| %d\t| %.2lf \t\t|\n", sellData[i].code, sellData[i].name, sellData[i].quantity, sellData[i].price);
            printf(" \t\t-------------------------------------------------\n");
            sum += sellData[i].price;
        }
        printf(" \n\n\n\t\tTotal Sold: $%.2lf\n", sum);
    }
    else
    {
        printf(" \n\n\n\t\tThere have been no sells yet.");
    }
    printf(" \n\n");
    *ind = 8;
    return;
}

void placeOrder(int *idn, int *itemID)
{
    int staged;
    printList();
    printf("\n \t\tPlace an order\n\t\t\tEnter Item ID or 9 to Exit or 8 to go to Main Menu\n\t\t\tItem ID: ");
    scanf("%d", &staged);
    if (staged == 9)
        *idn = staged;
    else if (staged == 8)
        *idn = 8;
    else
    {
        *idn = 10;
        *itemID = staged;
    }
}

void addItem(int *idn)
{
    char str[20];
    printf("\n\n\t\t\tEnter a unique valid integer item ID: ");
    scanf("%d", &COFFEEs[menuLength].code);
    printf("\t\t\tEnter the item name: ");
    getchar();
    gets(str);
    strcpy(COFFEEs[menuLength].name, str);
    printf("\t\t\tEnter the item price: ");
    scanf("%lf", &COFFEEs[menuLength].price);
    printf("\t\t\tEnter the item available quantity: ");
    scanf("%d", &COFFEEs[menuLength].inStock);
    printf("\t\tCongrats Item successfully added.\n");
    menuLength++;
    printList();
    *idn = 8;
    return;
}

void removeItem(int *identifier)
{
    int id, index, i, staged;
    printf("\n\n\t\tEnter a valid item ID to remove: ");
    scanf("%d", &id);
    for (i = 0; i < menuLength; i++)
    {
        if (COFFEEs[i].code == id)
        {
            printf("\t\tFound the item with ID: %d with name %s\n\t\t\tEnter 1 to confirm 0 to exit: ", COFFEEs[i].code, COFFEEs[i].name);
            scanf("%d", &staged);
            if (staged == 0)
            {
                *identifier = 8;
            }
            else if (staged == 1)
            {
                for (int j = i; j < menuLength; j++)
                {
                    COFFEEs[j].code = COFFEEs[j + 1].code;
                    strcpy(COFFEEs[j].name, COFFEEs[j + 1].name);
                    COFFEEs[j].price = COFFEEs[j + 1].price;
                    COFFEEs[j].inStock = COFFEEs[j + 1].inStock;
                }
                menuLength--;
                printList();
            }
            break;
        }
    }
    if (i > menuLength)
    {
        printf(" \t\tNo item found.");
    }
    *identifier = 8;
    return;
}

void updateQuantity(int *identifier)
{
    int id, quantity, i, staged;
    printf("\n\n\t\tEnter a valid item ID: ");
    scanf("%d", &id);
    for (i = 0; i < menuLength; i++)
    {
        if (COFFEEs[i].code == id)
        {
            printf("\t\tEnter the quantity to increment by: ");
            scanf("%d", &quantity);
            COFFEEs[i].inStock += quantity;
            printf("\t\tIncremented Successfully.....\n");
            printList();
            *identifier = 8;
            break;
        }
    }
    if (i == menuLength)
    {
        printf(" \t\tNo item found.");
        updateQuantity(identifier);
    }
    return;
}

int main()
{
    int identifier = 8, itemID, quantity;
    double itemPrice;
    char itemName[100];
    info();
    selectBasicOptionInfo();
    printf("\n \t\tSelect: ");
    scanf("%d", &identifier);
    while (identifier)
    {
        if (identifier == 1)
            placeOrder(&identifier, &itemID);
        else if (identifier == 2)
            addItem(&identifier);
        else if (identifier == 3)
            removeItem(&identifier);
        else if (identifier == 4)
            updateQuantity(&identifier);
        else if (identifier == 5)
            printStat(&identifier);
        else if (identifier == 10)
        {
            int i, staged;
            for (i = 0; i < menuLength; i++)
            {
                if (COFFEEs[i].code == itemID && COFFEEs[i].inStock > 0)
                {
                    printf("\n\n\t\t %s with Code %d is Available(%d) at price: %.2lf\n\t\t\tEnter Quantity to confirm or 0 to cancel: ", COFFEEs[i].name, COFFEEs[i].code, COFFEEs[i].inStock, COFFEEs[i].price);
                    scanf("%d", &staged);
                    if (staged == 0)
                        identifier = 8;
                    else if (COFFEEs[i].inStock >= staged)
                    {
                        COFFEEs[i].inStock -= staged;
                        quantity = staged;
                        itemPrice = COFFEEs[i].price;
                        strcpy(itemName, COFFEEs[i].name);
                        strcpy(sellData[soldLength].name, COFFEEs[i].name);
                        sellData[soldLength].code = COFFEEs[i].code;
                        sellData[soldLength].quantity = quantity;
                        sellData[soldLength].price = COFFEEs[i].price * quantity;
                        soldLength++;
                        identifier = 11;
                    }
                    else
                    {
                        printf("\t\tQuantity is not available.\n");
                        identifier = 8;
                    }
                    break;
                }
            }
            if (i == menuLength)
            {
                printf(" \t\tNo item found. Enter a valid itemId.\n\n\n\n");
                identifier = 8;
            }
        }
        else if (identifier == 11)
        {
            printf("\n\n\t\t-----------Bill-----------\n\n");
            printf("\t\tName    : %s\n\t\tQuantity: %d\n\t\tPrice   :  %.2lf\n\t\t----------------------\n\t\tTotal   : %.2lf\n\n", itemName, quantity, itemPrice, quantity * itemPrice);
            identifier = 8;
        }
        else if (identifier == 8)
        {
            printf("\n\n\n");
            selectBasicOptionInfo();
            printf("\n \t\tSelect: ");
            scanf("%d", &identifier);
        }
        else if (identifier == 9)
        {
            printf("\n\n\n\t\t\tClosing app.......\n\n");
            break;
        }
    }
    return 0;
}
