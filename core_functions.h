typedef struct item{
    char name[20];
    float calories, protein, fats, carb;
} food_item ;

#define BUFF_SIZE 32

float bmi_calc(int, float, int);
int fat_per(float, int, char);
void hrate(FILE *, int *, int);
void CalFatProteinCount(int);
void ReadFoods(FILE *, food_item *);
float StrToFloat(char *);
//void ClearBuffer(char *);
void food_calculate(food_item *);