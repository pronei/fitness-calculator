#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "core_functions.h"

int main()  {

    FILE *fp1, *fp2 ;
    int hrate_range[2], age, height, units;
    float bmi, weight;
    char gender, again;
    food_item food_array[20];
    int selectedchoice;

    //Open foods.txt
    fp1 = fopen("foods.csv", "r");
    
    fp2 = fopen("hrate_data.csv", "r");

    printf("Welcome to Fitness Calculator v1:\n\n");
    printf("-------------------------------------------------------------\n");
    printf("Select units : (1 for SI units, 2 for FPS system)\n");
    scanf("%d", &units);
    printf("Enter your gender : M for male, F for female\n");
    scanf(" %c", &gender);
    printf("Enter your age :\n");
    scanf("%d", &age);
    printf("Enter your weight:\n");
    scanf("%f", &weight);
    printf("Enter your height:\n");
    scanf("%d", &height);

    do  {
    printf("Table of functions:\n");
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("|     / /What would you like to do\\ \\           |\n");
    printf("|                                                 |\n");
    printf("|      1. Check BMI                               |\n");
    printf("|                                                 |\n");
    printf("|      2. Calculate Body Fat Percentage           |\n");
    printf("|                                                 |\n");
    printf("|      3. Know your Daily Calorie requirements    |\n");
    printf("|                                                 |\n");
    printf("|      4. Know your Daily Calorie intake          |\n");
    printf("|                                                 |\n");
    printf("|      5. Optimum Heart Rate                      |\n");
    printf("|                                                 |\n");
    printf("--------------------------------------------------\n");
    scanf("%d", &selectedchoice);
    switch (selectedchoice) {
        case 1:
            printf("Your BMI = %f\n", bmi_calc(height, weight, units));
            if ( bmi_calc(height, weight, units) < 18.5)       printf("Underweight\n");
            else if ( bmi_calc(height, weight, units) > 25)    printf("Overweight\n");
            else                                               printf("Normal\n");
            break;
        case 2:
            printf("Body Fat Percentage = %d %%\n", fat_per(bmi_calc(height, weight, units), age, gender));
            break;
        case 3:
            CalFatProteinCount(weight);
            break;
        case 4:
            ReadFoods(fp1, food_array);
            food_calculate(food_array);
            break;
        case 5:
            hrate(fp2, hrate_range, age);
            break;
        default:
            printf("Incorrect choice, select again\n");
            break;
    }
    printf("Try another function? Y/N\n");
    scanf(" %c", &again);
    } while (again == 'Y');

    return 0;
}