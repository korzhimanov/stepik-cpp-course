/* Напишите на языке C / C++ программу, определяющую номер треугольного числа
 * (см. также последовательность A000217 в «Энциклопедии целочисленных
 * последовательностей»).
 *
 * Примечание: число 0 (ноль) не считается принадлежащим ряду, который
 * считается начинающимся с единицы: 1, 3, 6, 10, 15, 21, 28, ... ﻿
 *
 * Вход: одно целое (возможно, со знаком «плюс» и символом «перевод строки» \n)
 * число в диапазоне от 1 до 9'223'372'036'854'775'807.
 *
 * Выход: порядковый номер поданного на вход числа в последовательности
 * треугольных чисел или 0 (ноль), если такого числа в последовательности нет.
 * Символ 0 (ноль) должен выдаваться и во всех случаях подачи на вход
 * некорректных (отрицательных и лежащих вне допустимого диапазона
 * положительных числовых, а также символьных / строковых) данных.
 */

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CORRECT_INPUT_MAX_LENGTH = 19; // number of digits in 9223372036854775807

uint64_t InputNumber() {
  char input[CORRECT_INPUT_MAX_LENGTH + 2]; // one more digit for sign and one - for '\0'
  uint64_t number = 0l;

  printf("Please, enter your number\n");
  int err = scanf("%20s", input); // read CORRECT_INPUT_MAX_LENGTH+1 characters
  if (err == -1){
      printf("Error!");
      return err;
  }
  printf("%lld\n%s: %li\n", INT64_MAX, input, strlen(input));
  if ((input[0] == '+' && strlen(input) > 20) || (input[0] != '+' && strlen(input) > 19)) {
      printf("String too long!");
      return 0;
  }
  if (input[0] == '-') {
    printf("Number seems to be negative!\n");
    return 0;
  }
  char *c = input;
  if (*c == '+') c++;
  if (strspn(c, "1234567890") != strlen(c)) {
    printf("Seems that your input is not an integer number!\n");
    return 0;
  }

  err = sscanf(input, "%llu", &number);

  if (number > INT64_MAX) {
    printf("Your number is too high!\n");
    return 0;
  }

  if (err == -1){
      printf("Error!");
      return 0;
  }

  printf("Your number is: %llu\n", number);
  return number;
}

int32_t ComputeTriangularNumber(int64_t number) {
  double number_f = (double)number;
  double result_f = 0.5*(sqrt(1. + 8.*number_f) - 1.);
  int64_t result = (int64_t)result_f;
  if (result*(result+1)/2 == number) return result;
  else return 0;
}

int main()
{
  uint64_t number = InputNumber();

  printf("It is # %ld in the sequence of triangular numbers.", ComputeTriangularNumber((int64_t)number));

  return 0;
}
