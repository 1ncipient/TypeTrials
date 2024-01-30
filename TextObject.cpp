#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <cctype>
#include <array>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string.h>

#include "TextObject.h"

using namespace std;

TextObject::TextObject(string inputString, bool generate) {
    if (generate == true) {
        this->text = apiCall(inputString);
    }
    else {
        this->text = inputString;
    }
    this->totalChars = this->text.length();
    vector<string> words = split(this->text, " ");
    this->totalWords = (int) words.size();
}

TextObject::~TextObject() {

}

string TextObject::getText() {
    return this->text;
}

int TextObject::getTotalChars() {
    return this->totalChars;
}

int TextObject::getTotalWords() {
    return this->totalWords;
}

string apiCall(string inputString) {
    string command = "curl -F 'text=" + inputString + "' -H 'api-key:57c1f1eb-a7d7-46b0-bcb3-e70202d56fba' https://api.deepai.org/api/text-generator";
    const char *cmd = command.c_str();

    string result = execSysCommand(cmd);

    // trim the resulting JSON string to only the relevant text section
    int start = result.find("\"output\": \"") + 11;
    int end = result.length() - 3;
    result = result.substr(start, end - start);

    // escape all JSON characters that were returned
    result = escapeJson(result);

    // trim the result to a maximum three sentences
    int count = 0;
    end = 0;
    for (int i = 0; i < (int) result.length(); i++) {
        end = i;
        if (result.at(i) == '.' || result.at(i) == '?' || result.at(i) == '!') {
            if (++count == 3) {
                break;
            }
        }
    }
    result = result.substr(0, end + 1);

    // remove remaining unicode encoding
    string arr[] = {"\\u005cn", "\\u005c", "\\u0022", "\\u2014" "\\u2026", "\\u2013", "u005cn", "u005c", "u0022", "u2014", "u2026", "u2013"};
    vector<string> targets(arr, arr + sizeof(arr)/sizeof(string));
    replaceAll(result, targets, " ");

    // replace all adjacent spaces with a single space
    string::size_type pos;
    while((pos = result.find("  ")) != string::npos) {
        result.replace(pos, 2, " ");
    }

    return result;
}

string execSysCommand(const char *cmd) {
    array<char, 512> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

string escapeJson(const string &inputString) {
    ostringstream o;
    for (int i = 0; i < (int) inputString.length(); i++) {
        char c = inputString.at(i);
        if (c == '"' || c == '\\' || ('\x00' <= c && c <= '\x1f')) {
            o << "\\u"
              << hex << setw(4) << setfill('0') << (int)c;
        }
        else {
            o << c;
        }
    }
    return o.str();
}

vector<string> split(string str, string sep) {
    char *cstr = const_cast<char *>(str.c_str());
    char *current;
    vector<string> arr;
    current = strtok(cstr, sep.c_str());
    while (current != NULL) {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}

void replaceAll(string &str, vector<string> targets, const string &to) {
    for (int i = 0; i < (int) targets.size(); i++) {
        string from = targets.at(i);

        if (from.empty()) {
            return;
        }

        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != string::npos) {
            str.replace(start_pos, from.length(), to);
            // In case 'to' contains 'from', like replacing 'x' with 'yx'
            start_pos += to.length();
        }
    }
}