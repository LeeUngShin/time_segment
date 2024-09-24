#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#define ROW_SIZE 6
#define SCR_SIZE ROW_SIZE * 6

void time_num(int n, int fnd[]);
void setFND(int fnd[], int screen[][SCR_SIZE], int cur);
void dispScreen(int screen[][SCR_SIZE]);

int main(void) {
  int screen[5][SCR_SIZE]; // ��ü �迭ũ��
  int fnd[8];              // ���� �Ѱ�
  int digit[6];            // �� �� �� �ִ� �迭
  char str[10];
  int hour, min, sec;
  for (int i = 0; i < 5; i++) { // �迭�� �� ��� . ä���ֱ�
    for (int j = 0; j < SCR_SIZE; j++) {
      screen[i][j] = '.';
    }
  }
  for (;;) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    hour = tm.tm_hour + 9; // ��
    min = tm.tm_min;       // ��
    sec = tm.tm_sec;       // ��
    printf("%02d:%02d:%02d\n", hour, min, sec);
    // 21�� 21�� 21��
    digit[5] = hour / 10; // 2
    digit[4] = hour % 10; // 1
    digit[3] = min / 10;  // 2
    digit[2] = min % 10;  // 1
    digit[1] = sec / 10;  // 2
    digit[0] = sec % 10;  // 1
    for (int j = 0; j < 6; j++) {
      time_num(digit[5 - j], fnd); // (����, ���� �ϳ� ǥ���� �迭)
      setFND(fnd, screen, j);
    }
    dispScreen(screen);
    printf("\n");
    Sleep(1000);
  }
  return 0;
}
void time_num(int n, int fnd[]) {
  int i, j;
  int segment[10][8] = {
      {0, 0, 1, 1, 1, 1, 1, 1}, // 0
      {0, 0, 0, 0, 0, 1, 1, 0}, // 1
      {0, 1, 0, 1, 1, 0, 1, 1}, // 2
      {0, 1, 0, 0, 1, 1, 1, 1}, // 3
      {0, 1, 1, 0, 0, 1, 1, 0}, // 4
      {0, 1, 1, 0, 1, 1, 0, 1}, // 5
      {0, 1, 1, 1, 1, 1, 0, 1}, // 6
      {0, 0, 1, 0, 0, 1, 1, 1}, // 7
      {0, 1, 1, 1, 1, 1, 1, 1}, // 8
      {0, 1, 1, 0, 0, 1, 1, 1}  // 9
  };
  for (i = 0; i < 8; i++) {
    fnd[i] = segment[n][7 - i];
  }
  // for (i = 0; i < 8; i++) {
  //   printf("%d ", fnd[7 - i]);
  // }
  // printf("\n");
}
void setFND(int fnd[], int screen[][SCR_SIZE], int cur) {
  char seg[5][5];
  int i, j;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      seg[i][j] = '.';
    }
  }
  if (fnd[0] == 1) // a
    for (i = 0; i < 5; i++)
      seg[0][i] = '#';
  if (fnd[1] == 1) // b
    for (i = 0; i < 3; i++)
      seg[i][4] = '#';
  if (fnd[2] == 1) // c
    for (i = 0; i < 3; i++)
      seg[i + 2][4] = '#';
  if (fnd[3] == 1) // d
    for (i = 0; i < 5; i++)
      seg[4][i] = '#';
  if (fnd[4] == 1) // e
    for (i = 0; i < 3; i++)
      seg[i + 2][0] = '#';
  if (fnd[5] == 1) // f
    for (i = 0; i < 3; i++)
      seg[i][0] = '#';
  if (fnd[6] == 1) // g
    for (i = 0; i < 5; i++)
      seg[2][i] = '#';
  // for (i = 0; i < 5; i++) {
  //   for (j = 0; j < 5; j++) {
  //     printf("%c", seg[i][j]);
  //   }
  //   printf("\n");
  // }
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      screen[i][cur * ROW_SIZE + j] = seg[i][j];
    }
  }
  // printf("\n");
  // for (i = 0; i < 5; i++) {
  //   for (j = 0; j < SCR_SIZE; j++) {
  //     printf("%c", screen[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n");
}
void dispScreen(int screen[][SCR_SIZE]) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < SCR_SIZE; j++) { // SCR_SIZE : 24
      printf("%c", screen[i][j]);
    }
    printf("\n");
  }
}