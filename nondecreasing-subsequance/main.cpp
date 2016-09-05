/* Напишите на языке C / C++ программу поиска максимальной по длине монотонно
 * неубывающей подпоследовательности во входной последовательности вещественных
 * чисел. Если таких подпоследовательностей несколько, выведите первую из них
 * (найденную при просмотре входного потока первой).
 *
 * Примечание: искомая подпоследовательность является «плотной», в ней нет
 * разрывов и посторонних элементов, включая числовые значения.
 *
 * Вход: одно целое N (длина последовательности; возможно, со знаком «плюс»),
 * за которым следует k вещественных чисел в любой разрешенной форме записи
 * (и, возможно, символ «перевод строки» /n). Если k = N, анализируется входная
 * последовательность вещественных целиком; если k > N, анализируется только N
 * первых (расположенных в традиционной записи слева) членов этой
 * последовательности. Если k < N (возможно, k = 0) или N < 2, входная
 * последовательность некорректна.
 *
 * Выход: два целых (натуральных), первое из которых L соответствует длине, а
 * второе — порядковому номеру i первого элемента найденной
 * подпоследовательности (принять i = 1, 2, 3, ...). Если входная
 * последовательность корректна, но искомая подпоследовательность не
 * обнаружена, вывести символ 0 (ноль). Во всех случаях подачи на вход
 * некорректных, в том числе символьных / строковых данных, вывести строку
 * [error] (вместе с квадратными скобками).
 */

#include <float.h>
#include <climits>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CORRECT_INPUT_MAX_LENGTH = 19;
int MAX_DBL_DIGITS = DBL_MAX_10_EXP + 2; // one char more for a sign

uint64_t ReadSequenceLength() {
  char input[CORRECT_INPUT_MAX_LENGTH + 2]; // one char more for a sign and one - for '\0'

  printf("Enter the sequence:\n");
  int err = scanf("%s ", input);
  if (err == -1){
      printf("Error of reading!");
      return 0;
  }
  printf("%s\n", input);
  if ((input[0] == '+' && strlen(input) > 20) || (input[0] != '+' && strlen(input) > 19)) {
      printf("String too long!");
      return 0;
  }
  if (input[0] == '-') {
    printf("Sequence length seems to be negative!\n");
    return 0;
  }
  char *c = input;
  if (*c == '+') c++;
  if (strspn(c, "1234567890") != strlen(c)) {
    printf("Seems that the sequence length is not an integer number!\n");
    return 0;
  }

  uint64_t sequence_length;

  err = sscanf(input, "%llu", &sequence_length);
  if (err == -1){
      printf("Error!");
      return 0;
  }

  printf("%llu\n", sequence_length);

  return sequence_length;
}

int ReadMember(double *memb) {
  char input[MAX_DBL_DIGITS];
  int err = scanf(" %s", input);
  if (err <= 0) {
    return err;
  }
  err = sscanf(input, " %lf", memb);
  if (err != strlen(input))
    return -1;
  else
    return err;
}

int ReadSequence(double* seq, uint64_t sequence_length) {
  for (uint64_t i = 0; i < sequence_length; i++) {
    int err = ReadMember(&seq[i]);
    printf("%llu %d ", i, err);
    if (err > 0) {
      printf("%f\n", i, seq[i]);
    }
    else {
      printf("Error!\n");
    }
    return err;
  }
}

void FindSubsequence(uint64_t sequence_length, double* seq){
  uint64_t subseq = 0, subseq_max = 0, subseq_len_max = 1;
  for (uint64_t i = 1; i < sequence_length; i++) {
    if (seq[i] < seq[i-1]) {
      if ((i - subseq) > subseq_len_max) {
        subseq_len_max = i - subseq;
        subseq_max = subseq;
      }
      subseq = i;
    }
  }
  if ((sequence_length - subseq) > subseq_len_max) {
    subseq_len_max = sequence_length - subseq;
    subseq_max = subseq;
  }
  if (subseq_len_max > 1) {
    printf("%llu %llu\n", subseq_len_max, subseq_max+1);
  }
  else {
    printf("%u", 0);
  }
}

int main()
{
  uint64_t sequence_length = ReadSequenceLength();

  double *seq = (double*)calloc(sequence_length, sizeof(double));
  int err = ReadSequence(seq, sequence_length);
  if (err <= 0)
    printf("[error]");

  FindSubsequence(sequence_length, seq);

  free(seq);
  return 0;
}
