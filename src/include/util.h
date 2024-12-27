#ifndef UTIL
#define UTIL

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

class Util {
public:
  enum randomType { smallLetter, capitalLetter, digit, specialCharacter, mix };

  static void urand() { srand(time(0)); }

  template <typename T>
  static typename std::enable_if<
      std::is_arithmetic<T>::value && !std::is_same<T, char>::value, T>::type
  randomNumber(T min, T max) {
    return rand() % (max - min + 1) + min;
  }

  static char randomChar(const randomType type) {
    char c;
    switch (type) {
    case randomType::smallLetter:
      c = randomNumber(97, 122);
      break;
    case randomType::capitalLetter:
      c = randomNumber(65, 90);
      break;
    case randomType::digit:
      c = randomNumber(48, 57);
      break;
    case randomType::specialCharacter:
      c = randomNumber(33, 47);
      break;
    case randomType::mix:
      c = randomChar(randomType(randomNumber(0, 3)));
      break;
    }
    return c;
  }

  static bool isSpecialCharacter(const char &c) { return 33 <= c && c <= 47; }

  static std::string randomWord(const randomType type, int wordLength,
                                bool withoutSpecialCharacters = true,
                                bool withoutDigits = false) {
    std::string word = "";
    for (int i = 1; i <= wordLength; i++) {
      char c = randomChar(type);

      // removing special characters
      if (withoutSpecialCharacters) {
        if (isSpecialCharacter(c)) {
          i -= 1;
          continue;
        }
      }

      // removing digits
      if (withoutDigits) {
        if (isdigit(c)) {
          i -= 1;
          continue;
        }
      }

      word += c;
    }
    return word;
  }

  // This method only return's key without special characters and number
  static std::string randomKey(short terms = 4, short termLength = 4,
                               bool useSmallLetters = false) {

    std::string key = "";

    for (short i = 1; i <= terms; i++) {
      std::string word = "";
      if (useSmallLetters) {
        word = randomWord(randomType::mix, termLength, true, true);
      } else {
        word = randomWord(randomType::capitalLetter, termLength, true, true);
      }

      key += word + '-';
    }

    // Removing last '-'
    key.pop_back();

    return key;
  }

  // This method only return's key without special characters and number
  static std::vector<std::string> randomKeys(int numberOfKeys, short terms = 4,
                                             short termLength = 4,
                                             bool useSmallLetters = false) {
    std::vector<std::string> keys = {};

    for (int i = 1; i <= numberOfKeys; i++) {
      keys.push_back(randomKey(terms, termLength, useSmallLetters));
    }
    return keys;
  }

  template <typename T> static void print(const std::vector<T> &v) {
    for (const T &str : v) {
      std::cout << str << '\n';
    }
  }

  template <typename T> static void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
  }

  static std::string tabs(short tabs) {
    std::string str = "";

    for (short i = 1; i <= tabs; i++) {
      str += '\t';
    }

    return str;
  }

  template <typename T>
  static typename std::enable_if<
      std::is_arithmetic<T>::value && !std::is_same<T, char>::value, void>::type
  fillWithRandomNumbers(std::vector<T> &v, T min, T max) {
    for (T &i : v) {
      i = randomNumber<T>(min, max);
    }
  }

  template <typename T>
  static typename std::enable_if<
      std::is_arithmetic<T>::value && !std::is_same<T, char>::value, void>::type
  fillWithRandomNumbers(T arr[], T arrayLength, T min, T max) {
    for (int i = 0; i < arrayLength; i++) {
      arr[i] = randomNumber(min, max);
    }
  }

  static void fillWithRandomStrings(std::vector<std::string> &v,
                                    randomType type, int wordLength,
                                    bool withoutSpecialCharacters = true,
                                    bool withoutDigits = false) {
    for (std::string &str : v) {
      str =
          randomWord(type, wordLength, withoutSpecialCharacters, withoutDigits);
    }
  }

  static void fillWithRandomStrings(std::string arr[], int arrayLength,
                                    randomType type, int wordLength,
                                    bool withoutSpecialCharacters = true,
                                    bool withoutDigits = false) {
    for (int i = 0; i < arrayLength; i++) {
      arr[i] =
          randomWord(type, wordLength, withoutSpecialCharacters, withoutDigits);
    }
  }

  static std::string encrypt(const std::string &str, short key) {
    std::string encryptedText = "";
    for (const char c : str) {
      encryptedText += c + key;
    }
    return encryptedText;
  }

  static std::string decrypt(const std::string &str, short key) {
    std::string decryptedText = "";
    for (const char c : str) {
      decryptedText += c - key;
    }
    return decryptedText;
  }

  template <typename T> static void shuffle(std::vector<int> &v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
      swap<T>(v[randomNumber(1, size) - 1], v[randomNumber(1, size) - 1]);
    }
  }

  static std::string repeat(const std::string &str, unsigned times) {
    std::string result = str;
    for (unsigned i = 1; i < times; i++) {
      result += str;
    }
    return result;
  }

  static std::string repeat(char c, unsigned times) {
    return repeat(std::to_string(c), times);
  }
};

#endif