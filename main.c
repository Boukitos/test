#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "vector.h"

int main(void)
{
    char arr[N] = {0};
    char cm[N] = {0}, cn[N] = {0}, ck[N] = {0};
    int m[N] = {0}, n[N] = {0}, k = 0;

    int sign_m = 1, sign_k = 1;
    int count_m = 0, count_n = 0;
    int err = 0;

    char char_digit[N];
    int count, new_digit[N], digit_sign;

    char c_mantissa[N];
    int mantissa[N], count_mantissa = count_m + count_n;

    printf("Программа реализует умножение числа в форме m.nEk на целое,\n");
    printf("где m - целая часть мантиссы, n - дробная, а k - порядок.\n");
    printf("При этом не допускатеся длина мантиссы m+n и целого q > 30;\n");

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
    if (-99999 > k || k > 99999)
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
    else if (count < 0)
      return INCORRECT_INPUT;
    sign_m *= digit_sign;
    snprintf(c_mantissa, sizeof(c_mantissa), "%s%s", cm, cn);
    count_mantissa = split_arr(c_mantissa, mantissa);
    result(mantissa, count_mantissa, new_digit, count, k, sign_m, count_n);

    return 0;
}
