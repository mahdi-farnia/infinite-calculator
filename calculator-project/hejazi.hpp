//
//  hejazi.hpp
//  calculator-project
//
//  Created by mahdi farnia on 10/10/1401 AP.
//

#ifndef hejazi_hpp
#define hejazi_hpp

#include <string>
#include <iostream>
using namespace std;

namespace hejazi {

int toInt(char& num); // yooooooooooo ha ha ha ha ha
string plus1(string num1, string num2);
void processingLength(string& num1, string& num2);
string putZero(string& num, int pcs);
string adding(char& num1, char& num2, int& mod);
void processingRes(int& res, int& mod);
string processingNegPlus(string& num1, string& num2, bool& isDoubleMinus, string& res);
string minus1(string num1, string num2);
string processingNegMinus(string& num1, string& num2, string& res, bool& isNegative);
int toInt(string num);
void deleteSign(string& num);
string reducing(string& num1, string& num2, int i);
void deleteZero(string& num);


string plus1(string num1, string num2) {
  bool isDoubleMinus = false;
  string res = "";
    res = processingNegPlus(num1, num2, isDoubleMinus, res);

  if (res.empty()) {
    processingLength(num1, num2);
    size_t length = num1.length();
    int mod = 0;

    for (long i = length - 1; i >= 0; --i) {
      string x = adding(num1[i], num2[i], mod);
      res = x + res;
    }
    if (isDoubleMinus)
      res = "-" + res;
  }
  return res;
}

string processingNegPlus(string& num1, string& num2, bool& isDoubleMinus, string& res) {


  if (num1[0] == '-' && num2[0] == '-') {
    isDoubleMinus = true;
    num1.erase(0, 1);
    num2.erase(0, 1);

  }

  if (num1[0] == '-' && num2[0] != '-') {
    num1.erase(0, 1);
    res = minus1(num2, num1);
  } else if (num2[0] == '-' && num1[0] != '-') {
    num2.erase(0, 1);
    res = minus1(num1, num2);
  }
  return res;
}

void processingLength(string& num1, string& num2) {
  if (num1.length() > num2.length()) {
    num2 = putZero(num2, num1.length() - num2.length());
  } else if (num1.length() < num2.length()) {
    num1 = putZero(num1, num2.length() - num1.length());
  }
}

string putZero(string& num, int pcs) {
  string zeros = "";
  for (int i = 0; i < pcs; i++)
    zeros += "0";
  num = zeros + num;
  return num;
}

string adding(char& num1, char& num2, int& mod) {
  int x = toInt(num1);
  int y = toInt(num2);
  int res = x + y + mod;
  processingRes(res, mod);
  return to_string(res);
}

void processingRes(int& res, int& mod) {
  if (res > 9) {
    mod = res / 10;
    res = res % 10;
  } else {
    mod = 0;
  }
}

int toInt(char& num) {
  return int(num - '0');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

  string x = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
  string y = "-97";
  string z = "-479";
  string res =  plus1(z, y) ;

  //cout << res;

  string i = "439"; // i = 3
  string t = "349";
  cout << minus1("39", "-1");
  return 0;
}

string minus1(string num1, string num2) {
  string res = "";
  bool isNegative = false;
  res = processingNegMinus(num1, num2, res, isNegative);
  if (res.empty()) {
    processingLength(num1, num2);
    int length = num1.length();
    for (int i = length - 1; i >= 0; i--) {

      string x = reducing(num1, num2, i);
      res = x + res;
    }
    deleteZero(res);
    if (isNegative)
      res = "-" + res;
  }

  return res;
}

string processingNegMinus(string& num1, string& num2, string& res, bool& isNegative) {
  if (num1[0] != '-' && num2[0] == '-') {
    num2.erase(0, 1);
    res = plus1(num1, num2);
  }

  if (num1[0] == '-' && num2[0] != '-') {
    num2 = "-" + num2;
    res = plus1(num1, num2);
  }

  if (num1[0] != '-' && num2[0] != '-') {
    if (toInt(num2) > toInt(num1)) {
      isNegative = true;
      swap(num1, num2);
    }
  }

  if (num1[0] == '-' && num2[0] == '-') {
    deleteSign(num1);
    deleteSign(num2);
    if (toInt(num1) > toInt(num2)) {
      isNegative = true;

    } else {
      swap(num1, num2);
    }
  }
  return res;
}

//string reducing(string& num1, string& num2, int i) {
//  int x = toInt(num1[i]);
//  int y = toInt(num2[i]);
//  int back = toInt(num1[i - 1]);
//}

#endif /* hejazi_hpp */
