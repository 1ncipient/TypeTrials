#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <iomanip>

#include "TextObject.h"

using namespace std;

TextObject::TextObject(string inputString) 
{
    this->text = apiCall(inputString);
    this->totalChars = this->text.length();
    std::vector<std::string> words = split(this->text, " ");
    this->totalWords = (int) words.size();
}

TextObject::~TextObject() 
{

}

string TextObject::getText() 
{
    return this->text;
}

int TextObject::getTotalChars() 
{
    return this->totalChars;
}

int TextObject::getTotalWords() 
{
    return this->totalWords;
}

string apiCall(string inputString)
{
    string command = "curl -F 'text=" + inputString + "' -H 'api-key:57c1f1eb-a7d7-46b0-bcb3-e70202d56fba' https://api.deepai.org/api/text-generator";
    const char *cmd = command.c_str();

    std::string result = execSysCommand(cmd);
    int start = result.find("\"output\": \"") + 11;
    int end = result.length() - 3;

    std::string resultParse = escapeJson(result.substr(start, end - start));
    std::vector<std::string> resultSentences = split(resultParse, ".");

    // set it to the min of 4 sentences or the length of vector
    int vecSize = std::min(4, (int)resultSentences.size());

    std::string shortResult = "";
    for (int i = 0; i < vecSize - 1; i++)
    {
        shortResult += resultSentences.at(i) + ". ";
    }
    shortResult += resultSentences.at(vecSize - 1) + ".";

    replaceAll(shortResult, "\\u005cn", " ");
    replaceAll(shortResult, "\\u005c", " ");
    replaceAll(shortResult, "\\u0022", " ");
    replaceAll(shortResult, "u2014", " ");

    std::string::iterator new_end = std::unique(shortResult.begin(), shortResult.end(), adjacentSpaces);
    shortResult.erase(new_end, shortResult.end());

    std::cout << "\n" + shortResult + "\n" << std::endl;

    return shortResult;
}

std::vector<std::string> split(std::string str, std::string sep)
{
    char *cstr = const_cast<char *>(str.c_str());
    char *current;
    std::vector<std::string> arr;
    current = strtok(cstr, sep.c_str());
    while (current != NULL)
    {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}

bool adjacentSpaces(char lhs, char rhs) { 
    return (lhs == rhs) && (lhs == ' '); 
}

std::string escapeJson(const std::string &inputString)
{
    std::ostringstream o;
    for (int i = 0; i < inputString.length(); i++)
    {
        char c = inputString.at(i);
        if (c == '"' || c == '\\' || ('\x00' <= c && c <= '\x1f'))
        {
            o << "\\u"
              << std::hex << std::setw(4) << std::setfill('0') << (int)c;
        }
        else
        {
            o << c;
        }
    }
    return o.str();
}

void replaceAll(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::string execSysCommand(const char *cmd)
{
    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[])
{
    TextObject *test = new TextObject("I just want to eat a banana.");
    cout << test->getText() << endl;
    cout << test->getTotalChars() << endl;
    cout << test->getTotalWords() << endl;
}