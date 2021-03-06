#include <iostream>
#include <cmath>
#include <cctype>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <list>
#include <stack>
#include <cstring>

using namespace std;

void operate(unsigned operations[10][10], unsigned clocks2[10], int op_num,
             int op_count) {
  for (int i = 1; i <= 9; i++) {
    clocks2[i] += operations[op_num][i] * op_count;
    clocks2[i] %= 4;
  }
}

int main() {
  //保存原始的时钟状态
  unsigned clocks[10] = {0};

  //保存最后最少的移动次数，最多也就是27次
  int min_res = 28, tmp = 0;
  //保存最小次数时候的移动方法
  unsigned min_op[10] = {0};

  // 9种操作对应数组
  unsigned operations[10][10] = {
      {0},
      // A  B  C D  E F  G  H  I
      {0, 1, 1, 0, 1, 1, 0, 0, 0, 0},  // op1: ABDE
      {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},  // op2: ABC
      {0, 0, 1, 1, 0, 1, 1, 0, 0, 0},  // op3: BCEF
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0},  // op4: ADG
      {0, 0, 1, 0, 1, 1, 1, 0, 1, 0},  // op5: BDEFH
      {0, 0, 0, 1, 0, 0, 1, 0, 0, 1},  // op6: CFI
      {0, 0, 0, 0, 1, 1, 0, 1, 1, 0},  // op7: DEGH
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},  // op8: GHI
      {0, 0, 0, 0, 0, 1, 1, 0, 1, 1}   // op9: EFHI
  };

  //移动操作改变数据clocks2，而clocks备份源数据
  unsigned clocks2[10] = {0};

  //记录每种移动方法操作次数
  unsigned op[10] = {0};

  //保存枚举移动1,2,3的64种执行情况
  unsigned move123[64][3];

  unsigned num, divide_num;
  for (int i = 0; i < 64; i++) {
    num = i;

    //将10进制i转换为对应的4进制move123[i]
    for (int j = 2; j >= 0; j--) {
      divide_num = (unsigned)num / 4;
      move123[i][j] = num - divide_num * 4;
      num = divide_num;
    }
  }

  for (int i = 1; i <= 9; i++) cin >> clocks[i];

  //枚举移动1,2,3的64种执行次数，计算出移动4-9的移动次数，判断是否满足最后条件，记录总次数
  for (int i = 0; i < 64; i++) {
    memcpy(clocks2, clocks, sizeof(unsigned) * 10);
    memset(op, 0, sizeof(unsigned) * 10);

    for (int j = 1; j <= 3; j++) {
      op[j] = move123[i][3 - j];
      operate(operations, clocks2, j, op[j]);
    }

    //移动操作4,5,6的次数分别由时钟A,B,C的状态决定
    for (int j = 4; j <= 6; j++) {
      op[j] = (4 - clocks2[j - 3]) % 4;
      operate(operations, clocks2, j, op[j]);
    }

    //移动操作7,9的次数分别由时钟D,F的状态决定
    op[7] = (4 - clocks2[4]) % 4;
    operate(operations, clocks2, 7, op[7]);
    op[9] = (4 - clocks2[6]) % 4;
    operate(operations, clocks2, 9, op[9]);

    //判断E是否为0，GHI是否相等
    if (clocks2[5] == 0 && clocks2[7] == clocks2[8] &&
        clocks2[8] == clocks2[9]) {
      op[8] = (4 - clocks2[7]) % 4;
      tmp = 0;
      for (int j = 1; j <= 9; j++) tmp += op[j];
      if (tmp < min_res) {
        min_res = tmp;
        memcpy(min_op, op, sizeof(unsigned) * 10);
      }
    }
  }

  //非零项排序
  vector<unsigned> res;
  for (int i = 1; i <= 9; i++) {
    if (min_op[i] != 0) {
      res.push_back(i);
      min_op[i]--;
      i--;
    }
  }

  sort(res.begin(), res.end());

  for (vector<unsigned>::iterator it = res.begin(); it != res.end(); it++)
    cout << *it << ' ';

  cout << "\n";

  return 0;
}
