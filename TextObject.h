
#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>
#include <vector>

/**
 * @brief A TextObject which represents the resulting parsed
 * text from an AI auto text generation API call
 * 
 * @author 1ncipient
 */
class TextObject { 
    public:
        /**
         * @brief Construct a new Text Object:: Text Object object
         * 
         * @param inputString The desired text to be used for AI auto-text generation
         */
        TextObject(std::string inputString, bool generate);

        /**
         * @brief Destroy the Text Object:: Text Object object. Empty destructor
         * 
         */
        ~TextObject();

        /**
         * @brief Return the object's AI generated text
         * 
         * @return string The AI's auto generated text
         */
        std::string getText();

        /**
         * @brief Return the total number of chars from the AI's auto generated text
         * 
         * @return int The total number of chars from the AI's auto generated text
         */
        int getTotalChars();

        /**
         * @brief Return the total number of words from the AI's auto generated text
         * 
         * @return int The total number of words from the AI's auto generated text
         */
        int getTotalWords();

    private:
        /** @brief The AI auto generated text for the TextObject object */
        std::string text;

        /** @brief The total number of characters in the AI auto generated text */
        int totalChars;

        /** @brief The total number of words in the AI auto generated text */
        int totalWords;
};

/**
 * @brief Free helper function that supports making a cURL request to the API and parsing the returned string
 * 
 * @param inputString The desired text to be used for AI auto-text generation
 * @return string The parsed AI auto generated text
 */
std::string apiCall(std::string inputString);

/**
 * @brief Free helper function to execute a system command and return the result as a string
 * 
 * @param cmd The desired system command to run
 * @return string The resulting stout of the system command
 */
std::string execSysCommand(const char *cmd);

/**
 * @brief Free helper function that removes JSON escape characters such as \n \t \r
 * 
 * @param inputString The desired JSON to be escaped represented as a string
 * @return string The escaped JSON represented as a string
 */
std::string escapeJson(const std::string &inputString);

/**
 * @brief Free helper function that splits a string on a seperator and returns a vector
 * 
 * @param str The input string to be split
 * @param sep The delimitter for the input to be split on
 * @return vector<string> A vector of strings as a result from the split
 */
std::vector<std::string> split(std::string str, std::string sep);

/**
 * @brief Free helper function that replaces all instances of elements in targets in a string with a desired replacement string
 * 
 * @param str The input string to have elements replaces
 * @param targets A vector of strings containing targets that will be replaced
 * @param to The replacement string
 */
void replaceAll(std::string &str, std::vector<std::string> targets, const std::string &to);

#endif // TEXTOBJECT_H