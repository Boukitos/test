#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define NEGATIVE -1
#define POSITIVE 1

#define N 100
#define INCORRECT_INPUT -1

//+m.nE+k

/* Считает количество символов в строке*/
int get_count(char* arr)
{
	int count = 0;
	while (arr[count] != '\0')
		count++;
	return count;
}

/* Выводит в консоль целочисленный массив */
void print_arr(int* arr, int count)
{
	printf("Int array: ");
	for (int i = 0; i<count; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

/* Считывает массив символов при вводе, возвращает кол-во символов */
int get_arr(char* init_arr)
{
	int count;
	scanf("%s", init_arr);
	count = get_count(init_arr);
	return count;
}

/* Проверяет строку на наличие в ней нечисловых символов
TRUE если иных символов нет, иначе FALSE */
int is_numeric_string(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]) == 0)
			return FALSE;
		i++;
	}
	return TRUE;
}

/* Проверяет наличие знака в строке, возвращает его, убирает из строки */
int is_sign_str(char* str)
{
	int count = get_count(str);
	int i = 0, j = 1;
	if (str[0] == '-')
	{
		while (str[j] != '\0')
		{
			str[i] = str[j];
			i++;
			j++;
		}
		str[count-1] = '\0';
		return NEGATIVE;
	}
	else if (str[0] == '+')
	{
		while (str[j] != '\0')
		{
			str[i] = str[j];
			i++;
			j++;
		}
		str[count-1] = '\0';
	}
	return POSITIVE;
}

/* Разбивает строку на числа, выносит в отдельный массив */
void split_arr(char* char_arr, int* int_arr)
{
	int i = 0;
	while (char_arr[i] != '\0')
	{
		int_arr[i] = char_arr[i] - '0';
		i++;
	}
}

/* Приводит строку к одному числу*/
int split_int(char* arr)
{
	int digit = '0' - arr[0];
	int i = 0, sum = 0;
	while (arr[i] != '\0')
	{
		digit = arr[i] - '0';
		sum = sum*10+digit;
		i++;
	}
	return sum;
}

/* Проверяет строку, разбивает её на массивы (две части мантиссы, порядок)*/
int get_correct_form(char* arr, int* m, int* n, int* k)
{
	char* cm, *cn, *ck;
	int sign_m = 1, sign_k = 1;
	cm = strtok(arr, ".");
	sign_m = is_sign_str(cm);
	cn = strtok(NULL, "E e");
	ck = strtok(NULL, "");
	sign_k = is_sign_str(ck);

	if (ck == NULL)
	{
		printf("Неправильная форма!\n");
		return INCORRECT_INPUT;
	}

	if (is_numeric_string(cm) != TRUE || is_numeric_string(cn) != TRUE || is_numeric_string(ck) != TRUE)
	{
		printf("Введено не число!\n");
		return INCORRECT_INPUT;
	}

	split_arr(cm, m);
	
	split_arr(cn, n);
	*k = split_int(ck);
	*k *= sign_k;

	return 0;
}

/* Тестики */
void unit_test()
{
	int m[N], n[N], k;
	char arr1[] = "2359139";
	char arr2[] = "12.124E18";
	char arr3[] = "12.124e18";
	char arr4[] = ".124E18";
	char arr5[] = "12.E18";
	char arr6[] = "string";
}

int main(void)
{
	char arr[N];
	int m[N], n[N], k;
	int count_m, count_n, count_k;
	get_arr(arr);
	get_correct_form(arr, m, n, &k);
	printf("%d", k);
	return 0;
}
