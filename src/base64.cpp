#include "base64.h"

void Base64::set(const std::vector<unsigned char> &in)
{
    buffer = in;
}

void Base64::set(const std::string &in)
{
    std::vector<unsigned char> temp;
    for (auto ch : in)
        temp.push_back(static_cast<unsigned char &&>(ch));
    buffer = temp;
}

std::vector<unsigned char> &Base64::get()
{
    return buffer;
}

std::string Base64::toString()
{
    return std::string(buffer.begin(), buffer.end());
}

void Base64::encode()
{
    std::vector<unsigned char> temp;

    int val1 = 0;
    int val2 = -6;
    for (auto ch : buffer)
    {
        val1 <<= 8;
        val1 += ch;
        val2 += 8;

        while (val2 >= 0)
        {
            int index = val1 >> val2;
            index &= 0b111111;
            temp.push_back(static_cast<unsigned char &&>(alfabetBase64[index]));
            val2 -= 6;
        }
    }

    if (val2 > -6)
        temp.push_back(static_cast<unsigned char &&>(alfabetBase64[((val1 << 8) >> (val2 + 8)) & 0b111111]));

    while (temp.size() % 4)
        temp.push_back('=');

    buffer = std::move(temp);
}

void Base64::decode()
{
    if (buffer.size() % 4 != 0)
        throw std::logic_error("Is not Base64.");

    bool isNotBase64 = false;

    for (auto ch : buffer)
        isNotBase64 |= (!isalnum(ch) && (ch != '/') && (ch != '+') && (ch != '='));

    if (isNotBase64)
        throw std::logic_error("Is not Base64.");

    std::vector<unsigned char> temp;

    int val1 = 0;
    int val2 = -8;
    for (auto ch : buffer)
    {
        val1 <<= 6;
        val1 += rb64[ch];
        val2 += 6;

        if (val2 >= 0)
        {
            temp.push_back(static_cast<unsigned char &&>((val1 >> val2) & 0b11111111));
            val2 -= 8;
        }
    }

    while (temp[temp.size() - 1] == 0xFF)
        temp.pop_back();

    buffer = std::move(temp);
}

unsigned long long int Base64::length() const
{
    return buffer.size();
}
