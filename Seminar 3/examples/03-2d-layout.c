// RUN-1: clang -Wall -Wextra 03-2d-layout.c -o d3 && ./d3
// int m[3][4] is 3 rows of 4 int. In memory it is one block of 12 ints, no pointer table.

#include <stdio.h>

int main(void) {
  int m[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  printf("sizeof m = %zu, sizeof m[0] = %zu, sizeof m[0][0] = %zu\n",
         sizeof m, sizeof m[0], sizeof m[0][0]);          // 48, 16, 4
  printf("rows = %zu, cols = %zu\n",
         sizeof m / sizeof m[0], sizeof m[0] / sizeof m[0][0]);

  printf("one row step = %td bytes, one element step = %td bytes\n",
         (char *)(m + 1) - (char *)m, (char *)(m[0] + 1) - (char *)m[0]);  // 16, 4

  printf("m[1][2] = %d, *(m[1] + 2) = %d, *(*(m + 1) + 2) = %d\n",
         m[1][2], *(m[1] + 2), *(*(m + 1) + 2));         // 7, 7, 7
  printf("&m[1][2] - &m[0][0] = %td elements = 1 * cols + 2\n",
         &m[1][2] - &m[0][0]);                          // 6

  for (int i = 0; i < 3; i++) {          // outer loop = rows, inner loop = columns
    for (int j = 0; j < 4; j++)
      printf("%4d", m[i][j]);
    puts("");
  }

  int *rows[3] = {m[0], m[1], m[2]};     // the same table through pointers
  printf("rows[2][3] = %d\n", rows[2][3]);              // 12

  int t[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};      // transpose on the spot
  for (int i = 0; i < 3; i++)
    for (int j = i + 1; j < 3; j++) {   // only above the diagonal
      int tmp = t[i][j]; t[i][j] = t[j][i]; t[j][i] = tmp;
    }
  printf("t[1][0] = %d, t[0][1] = %d   // the same element after the swap\n",
         t[1][0], t[0][1]);             // 2, 2

  return 0;
}
