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
    for (int i = 0; i<count; i++)
        printf("%d", arr[i]);
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

    if (cm == NULL || cn == NULL ||ck == NULL)
    {
        printf("Неверный формат ввода!\n");
        return INCORRECT_INPUT;
    }

    *sign_k = is_sign_str(ck);

    if (is_numeric_string(cm) != TRUE || is_numeric_string(cn) != TRUE || is_numeric_string(ck) != TRUE)
    {
        printf("Неверный формат ввода!\n");
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
        printf("Неверный формат ввода!\n");
        return INCORRECT_INPUT;
    }

    count = get_count(char_digit);

    split_arr(char_digit, digit);

    return count;
}

/* Переводит массив символов в число */
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

/* Переводит массив чисел в обратном порядке следования цифр */
void reverse(int* arr, int count)
{
  int i = 0, tmp;
  count -= 1;
  while (i != count/2)
  {
    tmp = arr[i];
    arr[i] = arr[count-i];
    arr[count-i] = tmp;
    i++;
  }
}

/* Подсчитывает и выводит результат */
void result(int* mantissa, int count_mantissa, int* digit, int count, int k, int sign_m, int count_n)
{
  int result[N] = {0};
  int current[N] = {0};
  reverse(mantissa, count_mantissa);
  reverse(digit, count);
  int i = 0, j = 0, tmp = 0, c = 0;

  int a, b, n;
  while (i < count)
  {
    j = 0, c = i;
    for (int i = 0; i < 99; i++)
      current[i] = 0;
    b = digit[i];
    while (j < count_mantissa)
    {
      a = mantissa[j];
      n = (a*b);
      current[c] += n%10;
      tmp = n/10;
      current[c+1] += tmp;
      j++;
      c++;
    }
    i++;
    for (int q = 0; q < c; q++)
    {
      result[q] += current[q];
      if (result[q] > 9)
      {
        result[q+1] += result[q]/10;
        result[q] = result[q]%10;
      }
    }
  }
  reverse(result, c);
  if (c > 30)
  {
    k += c-30;
    c = 30;
  }
  k += c-count_n;
  if (sign_m == -1)
    printf("-");
  printf("0.");
  print_arr(result, c);
  printf("e%d\n", k);
}
