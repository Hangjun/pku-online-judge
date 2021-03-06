#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int calc(int width, vector<int>& s) {
  int numchar = 0;
  int height = 0;
  for (int i = 0; i < s.size(); i++) {
    if (numchar + s[i] > width) {
      height++;
      numchar = s[i] + 1;
    } else {
      numchar += s[i] + 1;
    }
  }

  if (numchar > 0) height++;
  return (width + 2) * (height + 2);
}

int main() {
  vector<int> s;
  string str;

  while (cin >> str) {
    if (str == "," || str == "." || str == "?" || str == "!") {
      s[s.size() - 1]++;
    } else {
      s.push_back(str.length());
    }
  }

  int length = s.size() - 1;

  for (int i = 0; i < s.size(); i++) {
    length += s[i];
  }

  int min = (length + 2) * 3;

  int start = 0;
  for (int i = 0; i < s.size(); i++) {
    start += s[i] + 1;
    if (start >= length / 2) break;
  }

  int end = *max_element(s.begin(), s.end());

  int area;
  for (int i = start; i >= end; i--) {
    area = calc(i, s);
    if (area < min) {
      min = area;
    }
  }
  cout << min << endl;
  return 0;
}
