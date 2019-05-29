#include <iostream>
#include <string>
#include <windows.h>

#include "base64.h"

std::vector<unsigned char> loadFromFile(const std::string &path);

void uploadToFile(const std::string &path, const std::vector<unsigned char> &buffer);

int main()
{
    bool exitFail = true;
    do
    {
        Base64 base64;

        // Input.
        bool inputFail = true;
        do
        {
            std::string modeInput;
            std::cout << "Select input mode ('console' / 'file'): ";
            std::cin >> modeInput;

            if (modeInput == "file")
            {
                inputFail = false;

                std::string file;
                std::cout << "Enter the file path or 'default' for using file from the res folder: ";
                std::cin >> file;

//                if (file == "default")
//                    file = "../../res/testin.png";

                if (file == "default")
                    file = "../../res/input.txt";

                try
                {
                    base64.set(loadFromFile(file));

                    std::cout << base64.toString() << std::endl;
                    std::cout << "String is loaded from file." << std::endl;
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                    inputFail = true;
                }
            }
            else if (modeInput == "console")
            {
                inputFail = false;

                std::string str;
                std::cout << "Enter your string: ";
                std::cin >> str;

                base64.set(str);
            }
            else
            {
                std::cout << "Invalid command, try again." << std::endl;
            }

        } while (inputFail);

        // Encode / Decode.
        bool computeFail = true;
        do
        {
            std::string modeOperation;
            std::cout << "Select program mode ('encode' / 'decode'): ";
            std::cin >> modeOperation;

            if (modeOperation == "encode")
            {
                computeFail = false;
                base64.encode();
            }
            else if (modeOperation == "decode")
            {
                computeFail = false;

                try
                {
                    base64.decode();
                }
                catch (std::logic_error &e)
                {
                    std::cout << e.what() << std::endl;
                    computeFail = true;
                }
            }
            else
            {
                std::cout << "Invalid command, try again." << std::endl;
            }

        } while (computeFail);

        // Output to buffer / file
        bool outputFail = true;
        do
        {
            std::cout << base64.toString() << std::endl;

            std::string modeOutput;
            std::cout << "Select output mode ('clip' / 'file'): ";
            std::cin >> modeOutput;

            if (modeOutput == "file")
            {
                outputFail = false;

                std::string file;
                std::cout << "Enter the file path or 'default' for using file from the res folder: ";
                std::cin >> file;

//                if (file == "default")
//                    file = "../../res/testout.png";

                if (file == "default")
                    file = "../../res/output.txt";

                try
                {
                    uploadToFile(file, base64.get());
                    std::cout << "String is uploaded to file." << std::endl;
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                    outputFail = true;
                }
            }
            else if (modeOutput == "clip")
            {
                outputFail = false;

                try
                {
                    const size_t len = base64.length() + 1;
                    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
                    memcpy(GlobalLock(hMem), base64.toString().c_str(), len);
                    GlobalUnlock(hMem);

                    if (OpenClipboard(NULL)) {
                        EmptyClipboard();
                        SetClipboardData(CF_TEXT, hMem);
                        CloseClipboard();
                    }

                    std::cout << "String is copied to buffer." << std::endl;
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                    outputFail = true;
                }
            }
            else
            {
                std::cout << "Invalid command, try again." << std::endl;
            }

        } while (outputFail);

        // Exit / restart.
        bool escapeFail = true;
        do
        {
            std::string escape;
            std::cout << "Enter 'exit' to exit or 'run' to restart: ";
            std::cin >> escape;

            if (escape == "exit")
            {
                escapeFail = false;
                exitFail = false;
            }
            else if (escape == "run")
            {
                escapeFail = false;
            }
            else
            {
                std::cout << "Invalid command, try again." << std::endl;
            }

        } while (escapeFail);

    } while (exitFail);

    return EXIT_SUCCESS;
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