
                                // there's a number of function that need further more explenation about how to operate them which is not easy to explain using comments
                                // and if you face any bugs don't hesitate to contact me to fix them as soon as possible


                    //  the application can be used easly using the arrow keys to move between the store elements and options that you wanna pick
                    //  you can always press 'esc' key to return to the previous page
                    //  it's important to note that the application will not work correctly on some systems due to their terminal configurations
                    //  if it doesn't opens in full screen mode when you lunch it you'll face the previous issues mentioned above.


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

                                                        // this gotoxy function is used to move the cursor on the wanted location
void gotoxy(int x, int y)
{
    COORD c; 
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
                                                        // this function is used to determine the number of variable digits to draw the frame in the room_showcase function perfectly
int number_of_digits(int n)
{
    int s = 0;
    do
    { 
        n /= 10;
        s++;
    } while (n > 0);
    return s;
}


                                                        // this function is used to move the cursor in display that containes 2 options only, it onlt takes 'up arrow' , 'down arrow' , 'enter' and 'esc' keys as input
                                                        //  'up' and 'down' are used to move between the available options 'enter' is used to pick the option and 'esc' to return to the previous page
                                                        // it works by prinitng '>>>>' which is the cursor indicator in the wanted position using coordinates (x,y) and replace the previous position with 'space'
                                                        // to remove the old '>>>>' the function returns 1 for the first option, 2 for the second and 0 for pressing 'esc'

int display_move(int x, int y)
{
    char a;
    int X = x, Y = y;

    gotoxy(X,Y);
    printf(">>>>");
    while (TRUE)
    {
        a = getch();
        switch (a)
        {

        case 72:                    //    up
            if (Y == y + 2)
            {
                gotoxy(X, Y);
                printf("    ");
                Y -= 2;
                gotoxy(X, Y);
                printf(">>>>");
            }
            break;
        case 80:                    //    down
            if (Y == y)
            {
                gotoxy(X, Y);
                printf("    ");
                Y += 2;
                gotoxy(X, Y);
                printf(">>>>");
            }
            break;
        default:
            break;
        }

        if (a == 13 && ((Y == 43) || (X == 152 && Y == 12) || (X == 94 && Y == 14)))
            return 1;

        if (a == 13 && ((Y == 45) || (X == 152 && Y == 14) || (X == 94 && Y == 16)))
            return 2;

        if (a == 27)
            return 0;
    }
}

                                                        // this is the curor moving algorithme for the shwocase room we start by setting the cursor to the position (0,0) to gain sight
                                                        // on top of the window the cursor is set at the position (x,y) which is (5,12) at the first product it moves up and down
                                                        // by 66 lines to get to the products up and down it moves right and left by 15 to get to the products on left and right
                                                        // the number of movements the cursor can do is determined by the umber of products xhich is calculated by (n-1)/3 the first line is 0
                                                        // the cursor can move right based on the number of products in that line most lines are at 3, but if it's on the last line
                                                        // it calculates if the codrinates of the cursor are at the last product by (cordY*3 + cordX) and since this room works as a 2d array
                                                        // the last product index will be n-1 so we do the comparison like: (corY * 3 + corX) != number_of_cars - 1 and befors going down, it checks if
                                                        // the current coordinats won't go beyond the number of products to an empty space by:(corY * 3 + corX) < number_of_cars - 3
                                                        // the variables x, y, corX, corY, are static so that whenever you decide to return to the showcase_room the cursor will point at the item picked
                                                        // if 'enter' key is pressed the function returns the cursor position which is also the product index in the array
                                                        // if 'esc' key is pressed the function -1 which will cause you to return to the previous window

int showcase_room_move(int number_of_cars)
{
    gotoxy(0, 0);

    char a;
    int lines = ((number_of_cars - 1) / 3);
    static int x = 5, y = 12, corX = 0, corY = 0;

    gotoxy(x, y);
    printf(">>>>>");
    while (1)
    {
        a = getch();
        switch (a)
        {

        case 75: //    left
            if (corX != 0)
            {
                gotoxy(x, y);
                printf("     ");
                x -= 66;
                corX--;
                gotoxy(x, y);
                printf(">>>>>");
            }
            break;
        case 77:                                                //  right
            if (corX != 2 && (corY * 3 + corX) != number_of_cars - 1)
            {
                gotoxy(x, y);
                printf("     ");
                x += 66;
                corX++;
                gotoxy(x, y);
                printf(">>>>>");
            }
            break;
        case 72:                                                //  up
            if (corY != 0)
            {
                gotoxy(x, y);
                printf("     ");
                y -= 15;
                corY--;
                gotoxy(x, y);
                printf(">>>>>");
            }
            break;
        case 80:                                                //  down
            if (corY != lines && (corY * 3 + corX) < number_of_cars - 3)
            {
                gotoxy(x, y);
                printf("     ");
                y += 15;
                corY++;
                gotoxy(x, y);
                printf(">>>>>");
            }
            break;
        }

        if (a == 13 )
            return corY * 3 + corX;                             //  enter
        if (a == 27)
            return -1;                                          //  escp
    }
}
                                                        // this function reads the variabless from the .txt file and assign them to the specs array it starts by checking if the file exists, if it
                                                        // doesn't it tells us that no file was founf and returns -1 which will terminate the application in main(), if te file exists it reads the exisiting 
                                                        // 27 variables, the do while terminates if there's less then 27 variables or if the cursor reaches the end of file and it ends by returning the number 
                                                        // of lines read which is the number of items in the store

                                                        
int assign_variables(specs car[])
{
    int i = 0;
    current_file = fopen("garage.txt", "r");
    if (current_file == NULL)
    {
        printf("no file found\n");
        system("pause");
        return -1;
    }
    
    
    while (!feof(current_file) && fscanf(current_file, "%d,%55[^,],%55[^,],%55[^,],%55[^,],%55[^,],%55[^,],%55[^,],%d,%d,%d,%f,%f,%f,%c,%d,%55[^,],%d,%d,%d,%d,%d,%f,%f,%f,%f,%6999[^\n]\n", &car[i].id, car[i].manufacturer, car[i].model, car[i].chassis.Body_type, car[i].chassis.exterior_color, car[i].chassis.interior_color, car[i].chassis.drive_type, car[i].chassis.transmission, &car[i].price, &car[i].chassis.year, &car[i].mileage, &car[i].top_speed, &car[i].zero_to_one_undred_time, &car[i].motor.liters, &car[i].motor.shape, &car[i].motor.cylinders, car[i].motor.aspiration, &car[i].motor.E_motor, &car[i].motor.hp, &car[i].motor.torque, &car[i].motor.Displacement, &car[i].chassis.weight, &car[i].chassis.width, &car[i].chassis.length, &car[i].chassis.height, &car[i].chassis.wheelBase, car[i].description) == 27)
    {
        i++;
    }
    fclose(current_file);
    return i;
}
                                                        // this function is for adding items to the store it starts by drawing a frame that will allow the user to enter the required informations in
                                                        // it works by.........   it just works, after entering the item informations, it opens the .txt file in append mode to add the new item at 
                                                        // the end of of the file in the same format as the pre enterd data, the getchar() at different places is used to consume the '\n' at the end  
                                                        // of the previous input which is integer/float input

void add_item()
{
    current_file = fopen("garage.txt", "a");
    system("cls");
    int i,check_for_id=0;
    specs *add=(specs*)malloc(sizeof(specs));
    printf("\n\n                                                                   ________________________________________________________________________________________\n");
    for (i = 0; i < 38; i++)
    {
        printf("                                                                  |                                                                                        |\n");
    }
    printf("                                                                  |________________________________________________________________________________________|\n");
    do{
    gotoxy(81, 5);
    printf("id:               ");
    gotoxy(85, 5);
    scanf(" %d", &add->id);
    check_for_id=0;
    for ( i = 0; i < number_of_cars; i++)
    {
     
        if(car[i].id==add->id)
        check_for_id=1;
    }
    
    }while(check_for_id);

    getchar();
    gotoxy(81, 6);
    printf("CAR MANUFACTURER: ");
    gets(add->manufacturer);
    gotoxy(81, 7);
    printf("MODEL: ");
    gets(add->model);
    gotoxy(81, 8);
    printf("BODY TYPE: ");
    gets(add->chassis.Body_type);

    gotoxy(81, 9);
    printf("EXTERIOR COLOR: ");
    gets(add->chassis.exterior_color);

    gotoxy(81, 10);
    printf("INTERIOR COLOR: ");
    gets(add->chassis.interior_color);

    gotoxy(81, 11);
    printf("DRIVING TYPE: ");
    gets(add->chassis.drive_type);

    gotoxy(81, 12);
    printf("TRANSMISION : ");
    gets(add->chassis.transmission);

    gotoxy(81, 13);
    printf("PRICE: ");
    scanf(" %d", &add->price);

    gotoxy(81, 14);
    printf("YEAR: ");
    scanf(" %d", &add->chassis.year);

    gotoxy(81, 15);
    printf("MILEAGE: ");
    scanf(" %d", &add->mileage);

    gotoxy(81, 16);
    printf("TOP SPEED: ");
    scanf(" %f", &add->top_speed);

    gotoxy(81, 17);
    printf("0 TO 100 KM/H TIME: ");
    scanf(" %f", &add->zero_to_one_undred_time);

    gotoxy(81, 18);
    printf("ENGINE LITERS: ");
    scanf(" %f", &add->motor.liters);
    getchar();

    gotoxy(81, 19);
    printf("ENGINE SHAPE: ");
    gets(add->motor.shape);

    gotoxy(81, 20);
    printf("NUMBER OF ENGINE CYLANDERS: ");
    scanf(" %d", &add->motor.cylinders);
    getchar();

    gotoxy(81, 21);
    printf("ENGINE ASPIRATION TYPE: ");
    gets(add->motor.aspiration);

    gotoxy(81, 22);
    printf("NUMBER OF ELECTRIC ENGINES: ");
    scanf(" %d", &add->motor.E_motor);

    gotoxy(81, 23);
    printf("ENGINE HP: ");
    scanf(" %d", &add->motor.hp);

    gotoxy(81, 24);
    printf("ENGINE TORQUE: ");
    scanf(" %d", &add->motor.torque);

    gotoxy(81, 25);
    printf("ENGINE DISPLACEMENT: ");
    scanf(" %d", &add->motor.Displacement);

    gotoxy(81, 26);
    printf("WEIGHT: ");
    scanf(" %d", &add->chassis.weight);

    gotoxy(81, 27);
    printf("WIDTH: ");
    scanf(" %f", &add->chassis.width);

    gotoxy(81, 28);
    printf("LENGTH: ");
    scanf(" %f", &add->chassis.length);

    gotoxy(81, 29);
    printf("HEIGHT: ");
    scanf(" %f", &add->chassis.height);

    gotoxy(81, 30);
    printf("WHEELBASE: ");
    scanf(" %f", &add->chassis.wheelBase);
    getchar();

    gotoxy(81, 31);
    printf("ENTER A DESCRIPTION ABOUT THE CAR: ");
    gets(add->description);
    fprintf(current_file, "%d,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%f,%f,%f,%s,%d,%s,%d,%d,%d,%d,%d,%f,%f,%f,%f,%s\n", add->id, add->manufacturer, add->model, add->chassis.Body_type, add->chassis.exterior_color, add->chassis.interior_color, add->chassis.drive_type, add->chassis.transmission, add->price, add->chassis.year, add->mileage, add->top_speed, add->zero_to_one_undred_time, add->motor.liters, add->motor.shape, add->motor.cylinders, add->motor.aspiration, add->motor.E_motor, add->motor.hp, add->motor.torque, add->motor.Displacement, add->chassis.weight, add->chassis.width, add->chassis.length, add->chassis.height, add->chassis.wheelBase, add->description);
    fclose(current_file);
    free(add);
}
                                                        // this function is used to delete the passed item, it takes the item id as a parameter, and it works by opening the current file in reading mode and setting the cursor back
                                                        // at the beginning of the file and opening a new empty file in writing mode,it starts by checking the first value at the beginning of each line which is the item id and it reads
                                                        // the remaining of the line sperately if the line id matches the item id it skipps that line if it not it writes it and writes the remaining of the line which is in the form of 
                                                        // a string. it ends by deleting the previous file, and renaming the new file just like the old one

void delete_item(int item_id)

{
    FILE *current_file = fopen("garage.txt", "r"), *new_file = fopen("new_garage.txt", "w+");
    int count = 1, line_id;
    char line_to_read[2000];
    fseek(current_file, 0, SEEK_SET);
    while (fscanf(current_file, "%d,%1999[^\n]\n", &line_id, line_to_read) == 2)
    { 
        if (item_id != line_id)
            fprintf(new_file, "%d,%s\n", line_id, line_to_read);
    };
    
    fclose(current_file);
    fclose(new_file);
    remove("garage.txt");
    rename("new_garage.txt", "garage.txt");
}
                                                        // this is function diplayes the available cars in the store this do while loop is duplicated many times such that each one draws a specific line, and no i couldn't build
                                                        // it all in 3 if statements cuz the print statements would be too long and hard for a new user to understand the new_item variable is limited to draw 3 items
                                                        // on each line and if the amount of cars already displyed and the currentin line item is less then the totla amount of cars, for example if the difference is
                                                        //  =2 it will draw only 2 items on the new line etc...,  strlen and number-of didgts here are used to determine the amount of space that their string and int
                                                        // variables will take to print (blank) on the remaining space until it reaches the limit of space that  i decided to keep for each car displayed which is just 
                                                        // about 54 characters, at the end of each loop, 'i' value changes depending on the  number  of elements printed, assuming that item_in_line is equal to 3
                                                        // i will be increased by 3 and then reduced by 1  i=i-1 due to the fact that at the end of each loop 'i' is  increased by 1 so they cancel eachother
                                                        // i+= item_in_line-1,  the function calls the showcase_room_move function as a return value which will return the coordinates of the choosen  item in the 
                                                        // form of  ( corY*3+corX ) 

int showcase_room(specs car[], int n)
{
    system("cls");
    int i, j, item_in_line = 0;



    
    printf("\n                                 ________________________________________________________________________________________________________________________________________________\n");
    printf("                                |                                                                                                                                                |\n");
    printf("                                |                                                                                                                                                |\n");
    printf("                                |                                                                   ");
    setColor(14);
    printf("Cars For Sale");
    setColor(15);
    printf("                                                                |\n");
    printf("                                |                                                                                                                                                |\n");
    printf("                                |________________________________________________________________________________________________________________________________________________|\n\n");
    printf("\n");
    for (i = 0; i < n; i++)
    {
       
        do
        {
            printf("             ____________________________________________________ ");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |                     ");
            setColor(8);
            printf(".--------.");
            setColor(7);
            printf("                     |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |                ");
            setColor(8);
            printf("____/_____|___ \\___");
            setColor(7);
            printf("                 |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |               ");
            setColor(8);
            printf("O   _   -  |  _    ,*");
            setColor(7);
            printf("                |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |               ");
            setColor(8);
            printf("'--(_)-------(_)--'");
            setColor(7);
            printf("                  |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |____________________________________________________|");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |                                                    |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |  ");
            setColor(14);
            printf("%s %s", car[i + item_in_line].manufacturer, car[i + item_in_line].model);
            setColor(7);
            for (j = 16 + strlen(car[i + item_in_line].manufacturer) + strlen(car[i + item_in_line].model); j < 65; j++)
                printf(" ");
            printf("|");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |                                                    |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |                                                    |");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |    ");
            setColor(8);
            printf("EUR %d", car[i + item_in_line].price);
            setColor(7);
            for (j = 22 + number_of_digits(car[i + item_in_line].price); j <= 65 - (number_of_digits(car[i + item_in_line].mileage) + number_of_digits(car[i + item_in_line].chassis.year) + 8); j++)
                printf(" ");
            setColor(8);
            printf("%d ", car[i + item_in_line].chassis.year);
            setColor(7);
            printf("|");
            setColor(8);
            printf(" %d km  ", car[i + item_in_line].mileage);
            setColor(7);
            printf("|");
        } while (item_in_line++ < 2 && i + item_in_line < n);
        printf("\n");
        item_in_line = 0;
        do
        {
            printf("            |____________________________________________________|");
        } while (item_in_line++ < 2 && i + item_in_line < n);

        
        i += item_in_line - 1;
        item_in_line = 0;

        printf("\n\n\n\n");
    }
    return showcase_room_move(number_of_cars);
}
                                                        // this is the purchase window it takes the specs array and the the picked item id as parameters and display the picked item in the frame as well as
                                                        // its price and the total price of the picked items down bellow, it also diplayes the instruction of how to use the function on the right side of the frame
                                                        // if the user taps the '+' key, it will call the showcase_room function which will redisplay all of the availabe items, by pressing 'enter' you will add that item
                                                        // to your purchase and items_to_sell will be increased by 1 and the item_number array will take the item id as a value but it will check first if you already picked 
                                                        // the item since that all cars are rare with only 1 in the stock by running the id through a loop and comparing it with the IDs in item_number array, if the 
                                                        // conter reaches the number of items to sell, then the item was not picked before and it will be added, if the ID is already in the array, the showcase_room function  
                                                        // will be caled again to pick a different item, then redrawe the purchase frame with the total items picked and their total price, if the user taps the 'enter' key  
                                                        // on the purchase window the buying process will be completed, and display a message to inform you that it's done, that's when the delete function will be called 
                                                        // using a loop to remove all of the purchased item, the functionwill recieve the IDs from the item_number array to delete them,, if the user taps 'esc' the operation 
                                                        // in the purchase list that the operation started with 
                                                        // will be terminated and return 0 and go back to the first item,        smart i know.....................

int purchase_window(specs car[], int starting_item_id)
{
    system("cls");
    char a;
    int y = 6, total = 0;
    int i, j, items_to_sell = 1, item_number[C],line_space=0,receipt_item_line;
    FILE *receipt=NULL;
    item_number[0] = starting_item_id;
    while (TRUE) 
    {
        total += car[item].price;
        system("cls");
        printf("                                                      ______________________________________________________________________________________________________\n");
        for (i = 0; i < 14 + items_to_sell*2; i++)
        {
            if (i == 2 || i == 10 + items_to_sell*2)
                printf("                                                     |______________________________________________________________________________________________________|\n");

            else
                printf("                                                     |                                                                                                      |\n");
        }
        printf("                                                     |______________________________________________________________________________________________________|\n");
        gotoxy(103, 2);
        setColor(14);
        printf("PURCHASE");
        gotoxy(160, 2);
        setColor(8);
        printf("PRESS ENTER TO CONFIRM PURCHASE"); 
        gotoxy(160, 4);
        printf("PRESS + TO ADD ANOTHER CAR");
        gotoxy(160, 6);
        printf("PRESS esc TO TERMINATE THE PROCESS");
        setColor(7);
        for (j = 0, y = 6; j < items_to_sell; j++)
        {

            gotoxy(55, y);
            printf("- %s %s  (%d)  %s ", car[item_number[j]].manufacturer, car[item_number[j]].model, car[item_number[j]].chassis.year, car[item_number[j]].chassis.exterior_color);
            
                gotoxy(145-number_of_digits(car[item_number[j]].price), y);
                setColor(8);
                printf("%d euro", car[item_number[j]].price);
                setColor(7);
            y += 2;
        }
        gotoxy(57, i-1);
        setColor(14);
        printf("TOTAL :");
        gotoxy(145-number_of_digits(total), i-1);
        printf("%d euro", total);
        setColor(7);
        gotoxy(0,0);
        
        a = getch(); 
        if (a == 13)
        {
            setColor(8);
            gotoxy(160, 10);
            printf(" __________________________________________");
            gotoxy(160, 11);
            printf("|                                          |");
            gotoxy(160, 12);
            printf("|  PURCHASE COMPLETED SUCCESSFULLY.        |");
            gotoxy(160, 13);
            printf("|                                          |");
            gotoxy(160, 14);
            printf("|  HEAD TO OUR ACCOUNTANT TO COMPLETE      |");
            gotoxy(160, 15);
            printf("|  THE TRANSACTION PROCESS.                |");
            gotoxy(160, 16);
            printf("|__________________________________________|");
            setColor(7);
            gotoxy(160, 44);
            system("pause");
            for (i = 0; i < items_to_sell; i++)
            {
                delete_item(car[item_number[i]].id);
            }
            receipt=fopen("receipt.txt","w+");
  
        fprintf(receipt,"                                                   ______________________________________________________________________________________________________\n");

    for (i = 0,j=0,receipt_item_line=5; i < 12 + items_to_sell; i++)
        {
            if(i==receipt_item_line && j<items_to_sell)
                {fprintf(receipt,"                                                  |  - %s %s  (%d)  %s", car[item_number[j]].manufacturer, car[item_number[j]].model, car[item_number[j]].chassis.year, car[item_number[j]].chassis.exterior_color);
                for(line_space=strlen(car[item_number[j]].manufacturer)+ strlen(car[item_number[j]].model)+ number_of_digits(car[item_number[j]].chassis.year)+ strlen(car[item_number[j]].chassis.exterior_color);line_space< 81-number_of_digits(car[item_number[j]].price);line_space++)
                fprintf(receipt," ");
                fprintf(receipt,"%d euro     |\n                                                  |                                                                                                      |\n",car[item_number[j]].price);
               receipt_item_line++;
               j++;
                }
             else if(i==1)
                fprintf(receipt,"                                                  |                                               F1RST MOTORS                                           |\n");
            else if (i == 2 || i == 8 + items_to_sell)
                fprintf(receipt,"                                                  |______________________________________________________________________________________________________|\n");


            else if(i==10+items_to_sell)
                {fprintf(receipt,"                                                  |    TOTAL:");
                for ( line_space=number_of_digits(total); line_space<82; line_space++)
                fprintf(receipt," ");
                fprintf(receipt,"%d EURO     |\n",total);}
                
            else
                fprintf(receipt,"                                                  |                                                                                                      |\n");
        }
        fprintf(receipt,"                                                  |______________________________________________________________________________________________________|\n");
        fclose(receipt);



            return 1;
        }
        if (a == 43)
        {
            while (TRUE)
            {
                item = showcase_room(car, number_of_cars);
                if(item==-1)
                break;
                for (i = 0; i < items_to_sell; i++)
                {
                    if (item == item_number[i])
                        break;
                }
                if (i == items_to_sell)
                    break;
            }
            if(item!=-1){
            item_number[j] = item;
            items_to_sell++;
            }
        }
        else if (a == 27)
            return 0;
    }
}

                                                        // this function displays a window that asks the user if he wants to confirm removing the item, and takes the input using the display_move function, if the user
                                                        // picks yes, it will simply call the delete_item function and return the value 1 when it ends, else it will return -1

int conferm_deleting_item_window(specs car)
{
    system("cls");
    int j;
    gotoxy(60, 6);
                    printf(" __________________________________________________________________________________________________________________\n");
    for (j = 0; j < 9; j++)
    {
    printf("\t\t\t\t\t\t\t    |                                                                                                                  |\n");
    }
    
    printf("\t\t\t\t\t\t\t    |__________________________________________________________________________________________________________________|\n");
    gotoxy(69,9);
    printf("confirm that you wanna remove the %s %s from the dealership", car.manufacturer, car.model);
    gotoxy(158,12);
    printf("YES");
    gotoxy(158,14);
    printf("NO");
    mode = display_move(152, 12);
    if(mode==1)
    {
    delete_item(car.id);
    return 1;
    }
    return -1;
    
}
                                                        // this function asks the user weather he wanna make changes in the stock or he can choose to see the showroom
                                                        // it will take the inpput suing the display_move function

int software_options_window()
{
    system("cls");
    int j;
    gotoxy(84, 9);
    printf("  ___________________________________________\n");
    for (j = 0; j < 10; j++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t     |                                           |\n");
    }
    gotoxy(84, 19);
    printf(" |___________________________________________|\n");
    gotoxy(92, 11);
    printf("SELECT THE SOFTWARE MODE:");
    gotoxy(100, 14);
    setColor(8);
    printf("STORAGE MANAGEMENT");
    gotoxy(100, 16);
    printf("ROOM SHOWCASE");
    setColor(7);
    return display_move(94, 14);
}
                                                        // this function asks the user weather he wants to make changes to the stock such as removing/adding an item to the .txt file
                                                        // it will take the inpput suing the display_move function

int stock_options()
{
    system("cls");
    int j;
    gotoxy(84, 9);
    printf("  ___________________________________________\n");
    for (j = 0; j < 10; j++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t     |                                           |\n");
    }
    gotoxy(84, 19);
    printf(" |___________________________________________|\n");
    gotoxy(92, 11);
    printf("WHAT DO YOU WANNA DO:");
    gotoxy(100, 14);
    setColor(8);
    printf("ADD A NEW CAR");
    gotoxy(100, 16);
    printf("REMOVE A CAR");
    setColor(7);
    return display_move(94, 14);
}

                                                        // this functon displayes the item informations it will take the inpput suing the display_move function


int display(specs car)
{
    system("cls");
    int i = 0, j, k = 0, l = 0, last_line = 0;
    char car_info[12][120];
    memset(car_info, '\0', sizeof(car_info));
    for (j = 0; car.description[j] != '\0'; j++)
    {
        car_info[last_line][l++] = car.description[j];
        if (car.description[j] == ' ')
            k++;
        if (k == 11)
        {
            car_info[last_line][--l] = '\0';
            last_line++;
            k = 0;
            l = 0;
        }
    }
    printf("    ____________________________________________________________________________________________________________________________________________________________________________________________________________\n");
    for (j = 0; j < 48; j++)
    {
        if(j==2 || j==5 || j==47)
         printf("   |____________________________________________________________________________________________________________________________________________________________________________________________________________|\n");
        else if(j==8)
            printf("   |\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  _________________________________________________________     |\n");
        else if(j==9 || j==10 || (j>11 && j<36) || j==37 || j==38)
            printf("   |\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t |                                                         |    |\n");
        else if(j==11 ||j== 36 || j== 39)
            printf("   |\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t |_________________________________________________________|    |\n");
        else
            printf("   |\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");

        }
    gotoxy(14, 5);
    setColor(14);
    printf("%s %s", car.manufacturer, car.model);
    gotoxy(183, 5);
    printf("%d euro", car.price);
    gotoxy(167, 11);
    printf("SPECIFICATION ");
    gotoxy(14, 15);
    printf("DESCRIPTION:");
    gotoxy(14, 30);
    printf("MORE INFORMATION:");
    setColor(7);
    gotoxy(14, 18);
    printf("MAXIMUM POWER: ");
    setColor(8);
    printf("%d HORSEPOWER", car.motor.hp);
    setColor(7);
    gotoxy(14, 19);
    printf("MAXIMUM TORQUE: ");
    setColor(8);
    printf("%d NM", car.motor.torque);
    setColor(7);
    gotoxy(14, 20);
    printf("MAXIMUM SPEED: ");
    setColor(8);
    printf("%.1f KM/H", car.top_speed);
    setColor(7);
    gotoxy(14, 21);
    printf("0-100 KM/H (62MPH) IN: ");
    setColor(8);
    printf("%.1f s", car.zero_to_one_undred_time);
    setColor(7);
    gotoxy(14, 22);
    printf("ENGINE DISPLACEMENT: ");
    setColor(8);
    printf("%d CC", car.motor.Displacement);
    setColor(7);
    gotoxy(14, 23);
    printf("OVERALL WEIGHT: ");
    setColor(8);
    printf("%d KG", car.chassis.weight);
    setColor(7);
    gotoxy(14, 24);
    printf("OVERALL WIDTH: ");
    setColor(8);
    printf("%.3f M", car.chassis.width);
    setColor(7);
    gotoxy(14, 25);
    printf("OVERALL LENGTH: ");
    setColor(8);
    printf("%.3f M", car.chassis.length);
    setColor(7);
    gotoxy(14, 26);
    printf("OVERALL HEIGHT: ");
    setColor(8);
    printf("%.3f M", car.chassis.height);
    setColor(7);
    gotoxy(14, 27);
    printf("OVERALL WHEELBASE: ");
    setColor(8);
    printf("%.3f M", car.chassis.wheelBase);
    setColor(7);
    gotoxy(150, 15);
    printf("YEAR                   ");
    setColor(8);
    printf("%d", car.chassis.year);
    setColor(7);
    gotoxy(150, 17);
    printf("MILAEGE                ");
    setColor(8);
    printf("%d KM", car.mileage);
    setColor(7);
    gotoxy(150, 19);
    printf("EXTERIOR COLOR         ");
    setColor(8);
    printf("%s", car.chassis.exterior_color);
    setColor(7);
    gotoxy(150, 21);
    printf("INTERIOR COLOR         ");
    setColor(8);
    printf("%s", car.chassis.interior_color);
    setColor(7);
    gotoxy(150, 23);
    printf("DRIVE TYPE             ");
    setColor(8);
    printf("%s", car.chassis.drive_type);
    setColor(7);
    gotoxy(150, 25);
    printf("ENGINE                 ");
    setColor(8);
    printf("%.1fL %s%d %s", car.motor.liters, car.motor.shape, car.motor.cylinders, car.motor.aspiration);
    gotoxy(173, 26);
    printf("ENGINE");
    if (car.motor.E_motor == 1)
    {
        gotoxy(180, 26);
        printf("+ E-MOTOR");
    }
    else if (car.motor.E_motor > 1)
    {
        gotoxy(180, 26);
        printf("+ %d E-MOTORS", car.motor.E_motor);
    }
    setColor(7);
    gotoxy(150, 28);
    printf("BODY TYPE              ");
    setColor(8);
    printf("%s", car.chassis.Body_type);
    setColor(7);
    gotoxy(150, 30);
    printf("TRANSMISSION           ");
    setColor(8);
    printf("%s", car.chassis.transmission);
    gotoxy(173, 31);
    printf("TRANSMISION");
    setColor(7);
    gotoxy(168, 39);
    setColor(14);
    printf("%d EURO", car.price);
    setColor(7);
    gotoxy(14, 32);
    setColor(8);
    puts(car_info[0]);
    gotoxy(14, 33);
    puts(car_info[1]);
    gotoxy(14, 34);
    puts(car_info[2]);
    gotoxy(14, 35);
    puts(car_info[3]);
    gotoxy(14, 36);
    puts(car_info[4]);
    gotoxy(14, 37);
    puts(car_info[5]);
    gotoxy(14, 38);
    puts(car_info[6]);
    gotoxy(14, 39);
    puts(car_info[7]);
    gotoxy(14, 40);
    puts(car_info[8]);
    gotoxy(14, 41);
    puts(car_info[9]);
    setColor(7);
    gotoxy(184,43);
    setColor(8);
    printf("SELL");
    gotoxy(184,45);
    printf("DELETE");
    setColor(7);

    return display_move(177, 43);
}
