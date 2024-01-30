#ifndef STATSCONTROLLER_H
#define STATSCONTROLLER_H

#include <string>

#include "DatabaseController.h"
#include "StatsObject.h"

/**
 * @brief A StatsController, acting as the means to store and access user statistics
 * 
 * @author 1ncipient
 */
class StatsController: public DatabaseController {
    protected:
        /** @brief The StatsObject containing various statistics (WPM, Accuracy...) of a current user
         */
        StatsObject userStats;

    public:
        /**
         * @brief Construct the StatsController. Empty constructor
         * 
         */
        StatsController();

        /**
         * @brief Destroy the StatsController. Empty destructor
         * 
         */
        ~StatsController();

        /**
         * @brief Return the StatsObject containing typing statistics of some user
         *
         * @param str The userID of user to get statistics of 
         * @return StatsObject Containing typing statistics of a user
         */
        StatsObject getStats(std::string);

        /**
         * @brief Set the StatsObject containing typing statistics for a user
         *
         * @param str userID of a user to set statistics for
         * @param StatsObject The StatsObject containing various typing statistics
         */
        void setStats(std::string, StatsObject);

        /**
         * @brief Create an html string representation of a user's statistics
         *
         * @param str userID of a user to get statistics for
         * @return str String containing html representation of all statistics for that user
         */
         std::string printStats(std::string);
};

#endif // STATSCONTROLLER_H