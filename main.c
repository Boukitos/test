#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define NEGATIVE -1
#define POSITIVE 1

#define N 100
#define INCORRECT_INPUT -1
#define MANTISSA_OVERFLOW -2
#define ORDER_OVERFLOW -3
#define DIGIT_OVERFLOW -4

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
int split_arr(char* char_arr, int* int_arr)
{
	int i = 0;
	int count = get_count(char_arr);
	while (char_arr[i] != '\0')
	{
		int_arr[i] = char_arr[i] - '0';
		i++;
	}
	return count;
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

/* Строку str1 заменяет строкой str2*/
void replace_str(char* str1, char* str2)
{
	int i = 0;
	while (str1[i] != '\0')
	{
		str2[i] = str1[i];
		i++;
	}
}

/* Проверяет строку, разбивает её на массивы (две части мантиссы, порядок)*/
int get_correct_form(char* arr, char* cm1, char* cn1, char* ck1, int* sign_m, int* sign_k)
{

	char* cm = cm1, *cn = cn1, *ck = ck1;
	cm = strtok(arr, ".");
	*sign_m = is_sign_str(cm);
	cn = strtok(NULL, "E e");
	ck = strtok(NULL, "");
	*sign_k = is_sign_str(ck);

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
	replace_str(cm, cm1);
	replace_str(cn, cn1);
	replace_str(ck, ck1);
	return 0;
}

/* Читает строку символов, переводит её в массив чисел */
int get_digit(char* char_digit, int* digit, int* digit_sign)
{
	int count;
	get_arr(char_digit);

	*digit_sign = is_sign_str(char_digit);

	int err = is_numeric_string(char_digit);

	if (err == FALSE)
	{
		printf("Введено не число!");
		return INCORRECT_INPUT;
	}

	count = get_count(char_digit);

	split_arr(char_digit, digit);

	return count;
}

int split_int_arr(int* arr, int count)
{
	int digit = arr[0];
	int sum = 0;
	for (int i = 0; i < count; i++)
	{
		digit = arr[i];
		sum = sum*10+digit;
	}
	return sum;
}

int main(void)
{
	char arr[N];
	char cm[N] = {0}, cn[N] = {0}, ck[N] = {0};
	int m[N] = {0}, n[N] = {0}, k = 0;

	int sign_m = 1, sign_k = 1;
	int count_m = 0, count_n = 0;
	int err = 0;

	char char_digit[N];
	int count, new_digit[N], digit_sign;

	char c_mantissa[N];
	int mantissa[N], count_mantissa = count_m + count_n;

	printf("Введите число в форме m.nEk: ");
	get_arr(arr);
	err = get_correct_form(arr, cm, cn, ck, &sign_m, &sign_k);

	if (err != 0)
	{
		return INCORRECT_INPUT;
	}

	count_m = get_count(cm);

	if(count_m+count_n > 30)
	{
		printf("Переполнение мантиссы!\n");
		return MANTISSA_OVERFLOW;
	}
	k = split_int(ck);
	k *= sign_k;
	k += count_m;
	if (-99999 >= k >= 99999)
	{
		printf("Переполнение порядка!\n");
		return ORDER_OVERFLOW;
	}

	printf("Введите число, на которое необходимо умножить: ");
	count = get_digit(char_digit, new_digit, &digit_sign);
	if (count > 30)
	{
		printf("Слишком большое число!\n");
		return DIGIT_OVERFLOW;
	}

	snprintf(c_mantissa, sizeof(c_mantissa), "%s%s", cm, cn);
	count_mantissa = split_arr(c_mantissa, mantissa);
	print_arr(mantissa, count_mantissa);
	printf("Sign of mantissa: %d\n", sign_m);
	print_arr(new_digit, count);
	printf("Sign of digit: %d\n", sign_k);
	printf("k = %d\n", k);

	return 0;
}
