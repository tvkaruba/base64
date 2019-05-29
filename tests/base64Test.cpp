#include <gtest/gtest.h>
#include "base64.h"

std::vector<unsigned char> loadFromFile(const std::string &path);

void uploadToFile(const std::string &path, const std::vector<unsigned char> &buffer);

std::string strTest = "test";

std::string strWiki = "Man is distinguished, not only by his reason, but by this singular passion from other animals, "
                      "which is a lust of the mind, that by a perseverance of delight in the continued and "
                      "indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";

std::string b64Wiki = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0"
                      "aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1"
                      "c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0"
                      "aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdl"
                      "LCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";

TEST(Base64, wikiTest)
{
    Base64 base64;

    base64.set(strWiki);

    base64.encode();
    ASSERT_EQ(b64Wiki, base64.getString());
    base64.decode();
    ASSERT_EQ(strWiki, base64.getString());

    base64.set(b64Wiki);

    base64.decode();
    ASSERT_EQ(strWiki, base64.getString());
    base64.encode();
    ASSERT_EQ(b64Wiki, base64.getString());
}


TEST(Base64, setAndGet)
{
    Base64 base64;

    ASSERT_EQ("", base64.getString());

    base64.set(strTest);
    ASSERT_EQ(strTest, base64.getString());
}

TEST(Base64, length)
{
    Base64 base64;

    ASSERT_EQ(0, base64.length());

    base64.set(strTest);
    ASSERT_EQ(strTest.length(), base64.length());
}

std::string inPathText = "../../res/input.txt";
std::string outPathText = "../../res/output.txt";

TEST(Base64, encodeAndDecodeText)
{
    Base64 base64;

    auto temp = loadFromFile(inPathText);
    base64.set(temp);

    base64.encode();
    ASSERT_NE(temp, base64.get());

    base64.decode();
    ASSERT_EQ(temp, base64.get());

    uploadToFile(outPathText, base64.get());
    ASSERT_EQ(loadFromFile(inPathText), loadFromFile(outPathText));
}

std::string inPathImg = "../../res/testin.png";
std::string outPathImg = "../../res/testout.png";

TEST(Base64, encodeAndDecodeImg)
{
    Base64 base64;

    auto temp = loadFromFile(inPathImg);
    base64.set(temp);

    base64.encode();
    ASSERT_NE(temp, base64.get());

    base64.decode();
    ASSERT_EQ(temp, base64.get());

    uploadToFile(outPathImg, base64.get());
    ASSERT_EQ(loadFromFile(inPathImg), loadFromFile(outPathImg));
}

std::vector<unsigned char> loadFromFile(const std::string &path)
{
    try
    {
        std::ifstream fin(path, std::ios::binary);

        if (!fin.is_open())
            throw std::logic_error("File not found.");

        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(fin), {});

        return buffer;
    }
    catch (std::logic_error &e)
    {
        throw std::logic_error(e.what());
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Any error in file loader.");
    }
}

void uploadToFile(const std::string &path, const std::vector<unsigned char> &buffer)
{
    try
    {
        std::ofstream fout(path, std::ios::binary);

        if (!fout.is_open())
            throw std::logic_error("File not found.");

        for (auto byte : buffer)
            fout << byte;
    }
    catch (std::logic_error &e)
    {
        throw std::logic_error(e.what());
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Any error in file loader.");
    }
}