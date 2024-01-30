#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>

/**
 * @brief A DatabaseController acting as the parent class for other classes that accesses/stores information, acting as a database
 * 
 * @author 1ncipient
 */
class DatabaseController {
    protected:
         /** @brief The path to the datafile acting as the database
         */
        std::string dataFile;

    public:
        /**
         * @brief Construct the DatabaseController. Empty constructor
         * 
         */
        DatabaseController();

        /**
         * @brief Destroy the DatabaseController. Empty destructor
         * 
         */
        ~DatabaseController();

        /**
         * @brief Return the path to the datafile of some information type/database
         * 
         * @return string The path to datafile
         */
        std::string getDatafile();

        /**
         * @brief Set the path to the datafile of some information type/database
         * 
         * @param str The new path to datafile
         */
        void setDatafile(std::string);
};

#endif // DATABASECONTROLLER_H