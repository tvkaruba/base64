#ifndef BASE64_BASE64_H
#define BASE64_BASE64_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Base64
{
private:
    std::string alfabetBase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::vector<int> rb64;

public:
    Base64()
    {
        rb64.resize(256, -1);
        for (int i = 0; i < 64; ++i)
            rb64[alfabetBase64[i]] = i;
    }

public:
    /// Задает строку.
    void set(const std::vector<unsigned char> &in);

    /// Задает строку.
    void set(const std::string &in);

    /// Возвращает строку.
    std::vector<unsigned char> &get();

    /// Возвращает строку.
    std::string toString();

    /// Возвращает длинну строки.
    unsigned long long int length() const;

    /// Кодирует строку.
    void encode();

    /// Декодирует строку.
    void decode();

private:
    /// Строка, с которой работает класс.
    std::vector<unsigned char> buffer;
};

#endif //BASE64_BASE64_H
