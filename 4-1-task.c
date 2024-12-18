#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
/**
* @brief Считывает введеное значение 
* @return Возвращает введенное значение
*/
int input(void);

/**
 * @brief Создает массив
 * @param n размер массива
 * @return Возвращает массив с n элементами
 */
int* get_array(const size_t n); 

/**
 * @brief Проверяет введенное число на неотрицательность
 * @param value вводимое число
 * @return Возвращает ошибку, если число отрицательно или равно 0
 */
int no_negativ_input(void);

/**
* @brief Проверяет массив
* @param array массив
* @return возвращает ошибку, в случае недостатка памяти для массива
*/
void check_array(const int* array);

/**
 * @brief Копирует исходный массив
 * @param array исходный массив
 * @param n число элементов массива
 * @return Возвращает скопированный массив
 */
int* copy(const int* const array, const size_t n);

/**
* @brief Заполняет массив случайными числами
* @param array массив
* @param n количество элементов в массиве
* @param min начало диапазона
* @param max конец диапазона
* @return возвращает массив, заполненный случайными числами
*/
void fill_array_random(int* array, const size_t n, const int min, const int max);

/**
* @brief Заполнение массива при помощи ввода элементов с клавиатуры
* @param array массив
* @param n количество элементов в массиве
* @return возвращает массив, заполненный числами, введеными вручную
*/
void fill_array_manual(int* array, const size_t n);

/**
 * @brief Выводит исходный массив
 * @param array массив
 * @param n количество элементов в массиве
 * @return Возвращает вывод исходного массива
*/
void print_array(const int* array, const size_t n);

/** 
 * @brief Находит сумму отрицательных элементов массива, кратных 10 
 * @param array Указатель на массив, который будет проверяться 
 * @param n Количество элементов в массиве 
 * @return Возвращает сумму отрицательных элементов, кратных 10
 */
int sum_ellement_no_pozitiv (const int* array, const size_t n);

/**
 * @brief Заменяет первые k элементов массива на те же элементы в обратном порядке
 * @param array Указатель на массив, который будет изменен
 * @param n Количество элементов в массиве
 * @param k Количество элементов для замены
 */
void reverse_first_k_elements(int* array, size_t n, size_t k);

/**
 * @brief Проверка, есть ли пара соседних элементов с заданным произведнием 
 * @return true, если есть пара; false, если нет
 */
bool presence_pair(int* array, size_t n, int target);

/**
* @param random заполнение массива случайными числами
* @param manual заполнение массива пользователем
*/
enum request
{
    Random, manual
};

/**
* @brief Точка входа в программу
* @return Возвращает 0 в случае успеха
*/
int main(void)
{
    printf("Введите размер массива: ");
    size_t n = no_negativ_input();
    int* array = get_array(n);

    printf("Random - %d\n", Random);
    printf("Manual - %d\n", manual);
    
    int choice = input();
    switch (choice)
    {
    case Random:
        srand(time(0));  // Инициализация генератора случайных чисел
        printf("введите минимальное значение интервала \n");
        const int min = input();
        printf("введите максимальное значение интервала \n");
        const int max = input();
        fill_array_random(array, n, min, max);
        break;
    case manual:
        fill_array_manual(array, n);
        break;
    default:
        errno = ERANGE;
        perror("Function does not exist\n");
        exit(EXIT_FAILURE);
        break;
    } 

    printf("Содержимое массива: ");
    print_array(array, n);

    int sum = sum_ellement_no_pozitiv(array, n);
    printf("Сумма отрицательных элементов, кратных 10: %d\n", sum);

    printf("Введите количество элементов для реверса: ");
    size_t k = no_negativ_input();
    reverse_first_k_elements(array, n, k);
    printf("Массив после реверса первых %zu элементов: ", k);
    print_array(array, n);

    int target;
    printf("Введите целевое произведение для проверки наличия пары соседних элементов: ");
    target = input();
    
    if (presence_pair(array, n, target)) {
        printf("Найдена пара соседних элементов с произведением %d.\n", target);
    } else {
        printf("Пара соседних элементов с произведением %d не найдена.\n", target);
    }

    free(array);
    return 0;
}
int input(void)
{
    int value = 0;
    int result = scanf("%d", &value);
    if (result != 1)
    {
        errno = EIO;
        perror("ошибка ввода");
        exit(EXIT_FAILURE);
    }
    return value;
}

int* get_array(const size_t n) 
{
    int* array = (int*)malloc(n * sizeof(int));
    return array;
}

int no_negativ_input(void)
{
    int value = input();
    if (value <= 0)
    {
        errno = EINVAL;
        perror("Значение должно быть больше или равно нулю");
        exit(EXIT_FAILURE);
    }
    return value;
}

void check_array(const int* array)
{
    if (array == NULL)
    {
        errno = ENOMEM;
        perror("недостаточно памяти");
        exit(EXIT_FAILURE);
    }
}

void fill_array_random(int* array, const size_t n, const int min, const int max)
{
    check_array(array);
    if (min > max)
    {
        errno = EINVAL;
        perror("минимум не может быть больше максимума");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < n; i++)
    {
        array[i] = (rand() % (max-min+1)) + min;
    }
}

void fill_array_manual(int* array, const size_t n)
{
    check_array(array);
    for (size_t i = 0; i < n; i++)
    {
        printf("введите элемент %zu: ", i);
        array[i] = input();
    }
}

int* copy(const int* array, const size_t n)
{
	check_array(array);
	int* coparray = get_array(n);
	for (size_t i = 0; i < n; ++i)
	{
		coparray[i] = array[i];
	}

	return coparray;
}

void print_array(const int* array, const size_t n)
{
    check_array(array);
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int sum_ellement_no_pozitiv (const int* array, const size_t n)
{
    int sum = 0;
    for (size_t i = 0; i < n; i += 1)
    {
        if (array[i] < 0 && array[i] % 10 == 0)
        {
            sum += array[i];
        }
    }
    return sum;
}
void reverse_first_k_elements(int* array, size_t n, size_t k) 
{
    if (k > n)
    {
        errno = EINVAL;
        perror("к не должно быть больше размера массива");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < k / 2; i++) 
    {
        int temp = array[i];
        array[i] = array[k - 1 - i];
        array[k - 1 - i] = temp;
    }
}

bool presence_pair(int* array, size_t n, int target) 
{
    for (size_t i = 0; i < n - 1; i++)
    {
        if (array[i] * array[i + 1]) - target < DBL_EPSILON; 
        {
            return true;
        }
    }
    return false;
}
