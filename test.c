#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "vector.h"

/* Читает строку символов, переводит её в массив чисел */
int test_get_digit(char* char_digit, int* digit, int* digit_sign)
{
    int count;

    *digit_sign = is_sign_str(char_digit);

    int err = is_numeric_string(char_digit);

    if (err == FALSE)
    {
        printf("Неверный формат ввода!\n");
        return INCORRECT_INPUT;
    }

    count = get_count(char_digit);

    split_arr(char_digit, digit);

    return count;
}

int test(char* arr, char* char_digit)
{
  char cm[N] = {0}, cn[N] = {0}, ck[N] = {0};
  int m[N] = {0}, n[N] = {0}, k = 0;

  int sign_m = 1, sign_k = 1;
  int count_m = 0, count_n = 0;
  int err = 0;

  int count, new_digit[N], digit_sign;

  char c_mantissa[N];
  int mantissa[N], count_mantissa = count_m + count_n;

  err = get_correct_form(arr, cm, cn, ck, &sign_m, &sign_k);

  if (err != 0)
  {
      return INCORRECT_INPUT;
  }

  count_m = get_count(cm);
  count_n = get_count(cn);

  if(count_m+count_n > 30)
  {
      printf("Переполнение мантиссы!\n");
      return MANTISSA_OVERFLOW;
  }
  k = split_int(ck);
  k *= sign_k;
  k += count_m;
  if (-99999 > k || k > 99999)
  {
      printf("Переполнение порядка!\n");
      return ORDER_OVERFLOW;
  }

  count = test_get_digit(char_digit, new_digit, &digit_sign);
  if (count > 30)
  {
      printf("Слишком большое число!\n");
      return DIGIT_OVERFLOW;
  }
  else if (count < 0)
    return INCORRECT_INPUT;
  sign_m *= digit_sign;
  snprintf(c_mantissa, sizeof(c_mantissa), "%s%s", cm, cn);
  count_mantissa = split_arr(c_mantissa, mantissa);
  printf("OUTPUT:");
  result(mantissa, count_mantissa, new_digit, count, k, sign_m, count_n);
  return 0;
}

int main(void)
{
  char arr1[N] = "12.14e12";
  char arr2[N] = "123.32e11";
  char arr3[N] = "string";
  char arr4[N] = "12.34e15";
  char arr5[N] = "9203.566e-124";
  char arr6[N] = "-123.584e521";
  char arr7[N] = "999999999999999999.9999009999999e12"; //31 символ
  char arr8[N] = "3421.3423e99999";
  char arr9[N] = "-8593.123e-21";
  char digit1[N] = "98547";
  char digit2[N] = "12.32e21";

  printf("~~~~~TEST_1~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr1, digit2);
  test(arr1, digit1);

  printf("\n~~~~~TEST_2~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr2, digit1);
  test(arr2, digit1);

  printf("\n~~~~~TEST_3~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr3, digit1);
  test(arr3, digit1);

  printf("\n~~~~~TEST_4~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr4, digit1);
  test(arr4, digit1);

  printf("\n~~~~~TEST_5~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr5, digit1);
  test(arr5, digit1);

  printf("\n~~~~~TEST_6~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr6, digit1);
  test(arr6, digit1);

  printf("\n~~~~~TEST_7~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr7, digit1);
  test(arr7, digit1);

  printf("\n~~~~~TEST_8~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr8, digit1);
  test(arr8, digit1);

  printf("\n~~~~~TEST_9~~~~~\n");
  printf("INPUT: \narray: %s\ndigit: %s\n", arr9, digit1);
  test(arr9, digit1);

  return 0;
}
