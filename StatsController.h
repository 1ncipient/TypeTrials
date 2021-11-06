#ifndef STATSCONTROLLER_H
#define STATSCONTROLLER_H

#include <string>
#include "DatabaseController.h"
#include "StatsObject.h"

class StatsController: public DatabaseController {
    protected:
        StatsObject userStats;

    public:
        // Constructor & Destructor
        StatsController();
        ~StatsController();

        // Getters/Setters for data members
        StatsObject getStats(std::string);
        void setStats(std::string, StatsObject);
};

#endif