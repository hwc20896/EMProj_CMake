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

            [[nodiscard]]
            int getQuestionCount(int gamemode = 0);

            std::vector<QuestionData> getQuestions(int gamemode, int count);
        private:
            sqlite::database db_{"data.db"};
    };
    inline Database database;
}

#endif