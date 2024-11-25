#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
 
/** 
 * @param USING_THIRD_VAR -  
 * @param DONT_USING_THIRD_VAR -  
 */ 
enum repuest{USING_THIRD_VAR, DONT_USING_THIRD_VAR}; 
 
/** 
 * @brief выбор варианта  
 * @return возвращает номер выбранного варианта 
 */ 
void menu(void); 
 
/** 
 * @brief считывает число 
 * @return число 
 */ 
double input(void); 
 
/**  
 * @brief точка входа в программу 
 * @return 0, в случае успеха  
 */ 
int main(void) 
{ 
    printf("Введите два числа\n"); 
    double a = input(), b = input();
    int choice = input(); 
    switch(choice) 
    { 
        case USING_THIRD_VAR: 
            printf("a = %lf, b = %lf\n", a, b); 
            double c = a; 
            a = b; 
            b = c; 
            printf("a = %lf, b = %lf\n", a, b); 
            break; 
        case DONT_USING_THIRD_VAR: 
            printf("a = %lf, b = %lf\n", a, b); 
            a = a + b; 
            b = a - b; 
            a = a - b; 
            printf("a = %lf, b = %lf\n", a, b); 
            break; 
        default: 
            printf("Неправильный ввод");
            exit(EXIT_FAILURE);
    } 
    return 0; 
} 
 
void menu(void) 
{ 
    printf("USING_THIRD_VAR - %d\n", USING_THIRD_VAR); 
    printf("DONT_USING_THIRD_VAR - %d\n", DONT_USING_THIRD_VAR); 
} 
 
double input(void) 
{ 
    double value = 0.0; 
    int result = scanf("%lf", &value); 
    if (result != 1) {  
        errno = EIO; 
        printf("Не удалось считать число"); 
        exit(EXIT_FAILURE); 
    }  
    return value; 
}
