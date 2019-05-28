#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "core_functions.h"

float StrToFloat(char *str)  {
    char *str_ptr = &str[0] ;
    int integral = 0 ;
    float fractional = 0 ;

    while (*str_ptr != '.' && *str_ptr != '\0')      //checks for either decimal pt or NULL char
        integral = integral*10 + (*(str_ptr++) - '0') ;
    for (int i = -1 ; *(++str_ptr) != '\0' ; --i)
        fractional += (*str_ptr - '0') * pow(10, i) ;

    return (float) (integral + fractional) ;
}

float bmi_calc(int h, float w, int units)    {

    if (units == 1)     return w*pow(100, 2)/pow(h, 2) ;
    else if (units == 2)    return (w*pow(100, 2)/pow(h, 2))*703 ;

}

int fat_per(float bmi, int age, char gender)  {

    float bf;
    if (gender == 'M')
        bf = (1.2*bmi) + (0.23*age) - 10.8 - 0.54 ;
    else
        bf = (1.2*bmi) + (0.23*age) - 0.54 ;
    return bf ;

}

void hrate(FILE *fp, int *hrate_range, int age)  {

    int hrate_array[20], *hrate_array_ptr = hrate_array, n ;
    for (int i = 0 ; i < 20 ; ++i)  hrate_array[i] = 0 ;
    float average_hrate = 0 ;
    char buffer[BUFF_SIZE], *buffer_ptr = buffer, ch = 0 ; //EOF = -1

    n = 220 - age;
    hrate_range[0] = n * 0.6;
    hrate_range[1] = n * 0.75;
    printf("The ideal heart rate range for your age is %d to %d\n", hrate_range[0], hrate_range[1]);

    while (ch != EOF) {

        while((ch = fgetc(fp)) != ',' && ch != EOF)       *(buffer_ptr++) = ch ;
        *buffer_ptr = '\0' ;
        
        *(hrate_array_ptr++) = (int) StrToFloat(buffer) ;
        //ClearBuffer(buffer);
        buffer_ptr = buffer ;
    }
    *hrate_array_ptr = '\0' ;
    hrate_array_ptr = hrate_array ;

    while (*hrate_array_ptr != '\0')    average_hrate += *(hrate_array_ptr++) ;
    average_hrate /= (hrate_array_ptr - hrate_array) ;
    printf("Your heart rate according to the sensor is %.2f\n", average_hrate);
    return ;
}

void CalFatProteinCount(int w) {

    float car, fat, pro, cal, wp ;
    int option;
    printf("\tEnter the your option:\n");
    printf("-----------------------------------\n");
    printf("|                                 |\n");
    printf("|   1. To Bulk                    |\n");
    printf("|                                 |\n");
    printf("|   2. To Maintain Same weight    |\n");
    printf("|                                 |\n");
    printf("|   3. To Cut(Reduce Weight)      |\n");
    printf("|                                 |\n");
    printf("-----------------------------------\n");
    scanf("%d",&option);
    wp = w * 2.20462 ;
    cal = wp * 18 ;
    fat = wp*4 + (wp/2)*9 ;
    car -= fat ;
    car /= 4 ;
    switch (option)    {
        case 1 :    //Bulk
            pro = cal * 1.5 ;
            fat += fat * 0.5 ;
            car += car * 0.2 ;
            break ;
        case 2 :    //Maintain
            pro = cal ;
            break ;
        case 3 :    //Cut
            pro = cal * 0.5 ;
            fat -= fat * 0.5 ;
            car -= car * 0.2 ;
            break ;
    }
    printf("Required Calories: %f\n", cal);
    printf("Required Protiens: %f\n", pro);
    printf("Required Fat : %f\n", fat);
    printf("Required Carbohydrates: %f\n", car);
    return ; 
}

void ReadFoods(FILE *fp, food_item food_array[])    {

    char buffer[BUFF_SIZE], *buffer_ptr = buffer, ch ; //EOF = -1
    int count = 0, index, i = 0 ;   //count is for one string between two commas

    do  {

        while ((ch = fgetc(fp)) != ',' && ch != '\n' && ch != EOF)       *(buffer_ptr++) = ch ;
        *buffer_ptr = '\0' ;

        count++ ;
        index = count % 5 ;
        
        switch (index)  {
            case 1 : //name of food
                strcpy(food_array[i].name, buffer) ;
                break ;
            case 2 :
                //first convert str to float and repeat for other cases
                food_array[i].calories = StrToFloat(buffer);
                break ;
            case 3 :
                food_array[i].protein = StrToFloat(buffer);
                break ;
            case 4 :
                food_array[i].fats = StrToFloat(buffer);
                break ;
            case 0 :
                food_array[i].carb = StrToFloat(buffer);
                break ;
        }
        //ClearBuffer(buffer);
        buffer_ptr = &buffer[0] ;
        i = count/5 ;

    } while (ch != EOF) ;
    return ;
}

/*
void ClearBuffer(char *buffer)  {
    char *buffer_ptr ;
    for (buffer_ptr = buffer ; buffer_ptr - buffer < BUFF_SIZE ; buffer_ptr++)  *buffer_ptr = 0 ;
    return ;
}
*/

void food_calculate(food_item food_array[])   {
    char current_entry[BUFF_SIZE], again ;
    int serving, item_found = 0 ;
    
    float total_values[4];
    for (int k = 0 ; k < 4 ; ++k)   total_values[k] = 0;
    
    printf("Available foods:\n\n");
    printf("======================================================================================\n\n");
    for (int i = 0 ; i < 20 ; ++i)      printf("%s\t", food_array[i].name);
    printf("\n====================================================================================\n\n");
    
    do  {
        printf("Enter the food you've eaten:\n");
        scanf("%s", current_entry);
        printf("Enter the amount of said food in number of servings (serving size = 100g) :\n");
        scanf("%d", &serving);
        printf("Have you eaten anything else? Y/N\n");
        scanf(" %c", &again);
        
        for (int i = 0 ; i < 20 ; ++i)  {
            if (strcmp(food_array[i].name, current_entry) == 0) {
                item_found = 1 ;
                total_values[0] += food_array[i].calories * serving ;
                total_values[1] += food_array[i].protein * serving ;
                total_values[2] += food_array[i].fats * serving ;
                total_values[3] += food_array[i].carb * serving ;
                break ;
            }
        }
        item_found == 1 ? item_found = 0 : printf("Entered food wasn't found\n");
        
        //ClearBuffer(current_entry);
    } while (again == 'Y');

    printf("Your total values are :\n");
    printf("Calories = %.2f kcal\n", total_values[0]);
    printf("Proteins = %.2fg\n", total_values[1]);
    printf("Fats = %.2fg\n", total_values[2]);
    printf("Carbohydrates = %.2fg\n\n", total_values[3]);
}