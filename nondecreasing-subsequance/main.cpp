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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int CORRECT_INPUT_MAX_LENGTH = 19;

uint64_t ReadSequanceLength() {
  char input[CORRECT_INPUT_MAX_LENGTH+2]; // one char more for a sign and one - for '\0'
  uint64_t sequence_length = 0;

  printf("Enter the sequence:\n");
  int err = scanf("%s ", input);
  if (err == -1){
      printf("Error of reading!");
      return 0;
  }
  printf("%s\n", input);

  sscanf(input, "%llu", &sequence_length);

  printf("%llu\n", sequence_length);

  return sequence_length;
}

void ReadSequance(double* seq, uint64_t sequence_length) {
  for (uint64_t i = 0; i < sequence_length; i++) {
    scanf(" %lf", &seq[i]);
    printf("%llu, %f\n", i, seq[i]);
  }
}

void FindSubsequance(uint64_t sequence_length, double* seq){
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
  printf("%llu, %llu\n", subseq_len_max, subseq_max+1);
}

int main()
{
  uint64_t sequence_length = ReadSequanceLength();

  double *seq = (double*)calloc(sequence_length, sizeof(double));
  ReadSequance(seq, sequence_length);

  FindSubsequance(sequence_length, seq);

  free(seq);
  return 0;
}
