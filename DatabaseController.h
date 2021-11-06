#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>

class DatabaseController {
    protected:
        std::string dataFile;

    public:
        // Constructor & Destructor
        DatabaseController();
        ~DatabaseController();

        // Getters/Setters for data members
        std::string getDatafile();
        void setDatafile(std::string);
};

#endif