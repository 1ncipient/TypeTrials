#include <string>
#include <vector>

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

class TextObject
{ 
    public:
        TextObject(std::string inputString);
        ~TextObject();
        std::string getText();
        int getTotalChars();
        int getTotalWords();

    private:
        std::string text;
        int totalChars;
        int totalWords;
};

// free helper functions used in the class
std::string apiCall(std::string inputString);
std::vector<std::string> split(std::string str, std::string sep);
bool adjacentSpaces(char lhs, char rhs);
std::string escapeJson(const std::string &inputString);
void replaceAll(std::string &str, std::vector<std::string> targets, const std::string &to);
std::string execSysCommand(const char *cmd);

#endif // TEXTOBJECT_H