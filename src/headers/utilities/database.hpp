#pragma once
#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <sqlite_modern_cpp.h>
#include <vector>
#include "utilities/questiondata.hpp"

namespace Data {
    class Database final {
        public:
            explicit Database() = default;
            ~Database() = default;

            /**
             * @brief Get the number of questions in the database for a specific gamemode.
             * @param gamemode The gamemode to get the question count for. 0 for all, 1 for 基本法, 2 for 憲法.
             * @return The number of questions in the database for the specified gamemode.
             */
            [[nodiscard]]
            int getQuestionCount(int gamemode = 0);

            /**
             * @brief Get a list of questions from the database.
             * @param gamemode The gamemode to get questions for. 0 for all, 1 for 基本法, 2 for 憲法.
             * @param count The number of questions to get. Default is 10.
             * @return A vector of QuestionData objects.
             */
            [[nodiscard]]
            std::vector<QuestionData> getQuestions(int gamemode, int count);
        private:
            sqlite::database db_{"data.db"};
    };
    inline Database database;
}

#endif