#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define C 77

                                                        // this is the struct attribute for the car engine

typedef struct
{
    char aspiration[C], shape[2];
    int torque, Displacement, E_motor, cylinders, hp;
    float liters; 
} engine;

                                                        // this is the struct attribute for the car body

typedef struct
{
    char Body_type[C], exterior_color[C], interior_color[C], drive_type[C], transmission[C];
    int year, weight;
    float width, length, height, wheelBase;
} Body;

                                                        // this is the main struct containing all of the variables

typedef struct
{ 
    char manufacturer[C], model[C], description[7000]; 
    int id, price, mileage;
    float top_speed, zero_to_one_undred_time;
    engine motor;
    Body chassis; 
} specs; 

int number_of_cars, mode, item, item_handeling, reset_file; 
char a,date[C];
FILE *current_file = NULL, *new_file = NULL;
specs car[C];

                                                        // this liberary containes all of the used functions

#include "storage.h"


                                                        // the purpose of using many while loops is to make the user return to the previous window without having
                                                        // to relaunch the entire programme from scratch 





int main()
{
     ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
    while (TRUE)
    {
                                                        // here the assign_variablesfunction returns the number of cars, if the return value is -1, it means that
                                                        // there's no file and the application terminates, else the application will continue   
        number_of_cars = assign_variables(car);


        if (number_of_cars == -1)
            return 1;
                                                        // here the sotware_options_window will return 0 if the user press 'esc' which will terminate the application
                                                        //  else if it returns 1 it will head to stock_options, if it return 2, it will head to the showcase_room
                                                        // the return value will be stored in the 'mode'
        mode = software_options_window();

        if (mode == 0)
            break;

        else if (mode == 1)
        {
            while (TRUE)
            {
                                                        // here the stock_options returns a value that will be stored in 'mode'if 0 the programme will return to the previous
                                                        // window, if 1 it will call the add item window, if 2 it will call he showcase_room function which will return the index
                                                        // of the variable that the user wishes to delete  and stores the index in 'item', and then call the conferm_deleting_window
                                                        // which will return 1 if the user removed the item and refull the specs array 'car' using assign_variable function
                mode = stock_options();

                if (mode == 0)
                    break;
                if (mode == 1) 
                {
                    add_item();
                    memset(car, '\0', sizeof(car));
                    number_of_cars = assign_variables(car);
                }
                else if (mode == 2)
                    while (TRUE)
                    {
                        item = showcase_room(car, number_of_cars);
                        if (item == -1)
                            break;
                            
                        item_handeling = conferm_deleting_item_window(car[item]);
                        if (item_handeling == 1)
                        {
                                memset(car, '\0', sizeof(car));
                                number_of_cars = assign_variables(car);
                        }
                    }
            }
        }

        else if (mode == 2)
            while (TRUE)
            {
                                                        // here the showcase_room function returns -1 if the user press 'esc' which will make the programme return to the previous
                                                        // window, else it will return (corY*3+corX) which represents the selected item index, then we the sidplay function is called
                                                        // to display that item informations which will return either 0 which will cause the programme to return to the previous 
                                                        // window, else if it returns 1 we call the sell function which will do the purchase proccess and assign the value 1 to reset_file
                                                        // variable, else if the display function returns 2, it will conferm_deleting_item window with the chosen item as parameters
                                                        // if that function returns 1 the item was deleted and the reset_file variable will get the value of 1
                                                        // at the end the end we check if reset_file variable got the value of 1, if yes that means that changes were made to the .txt file
                                                        // either delete or add, so we empty the array and call the assign_variables function and set the value of reset_file to 0 


                item = showcase_room(car, number_of_cars);

                if (item == -1)
                    break;

                while (TRUE)
                {

                    item_handeling = display(car[item]);

                    if (item_handeling == 0)
                        break;
                    else if (item_handeling == 1)
                    {
                        item_handeling = purchase_window(car, item);
                        if (item_handeling == 1)
                        reset_file = 1;
                    }

                    else if (item_handeling == 2)
                        while (TRUE)
                        {
                            item_handeling = conferm_deleting_item_window(car[item]);
                            if (item_handeling == 1)
                            
                                reset_file=1;
                            
                            break;
                        }

                    if (reset_file == 1)
                    {
                        memset(car, '\0', sizeof(car));
                        number_of_cars = assign_variables(car);
                        reset_file = 0;
                        break;
                    }
                }
            }
    }

    return 0;
}
