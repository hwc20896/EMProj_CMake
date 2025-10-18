#pragma once
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include "utilities/questiondata.hpp"
#include "utilities/defines.hpp"
#include "third_party/duckdb.h"

namespace EMProj_CMake_Backend {
    class Database final {
        SINGLETON_WITHOUT_CONSTRUCTOR(Database)
        public:
            void testDatabase() const;

            [[nodiscard]]
            int getQuestionCount(int gamemode) const;

            [[nodiscard]]
            std::vector<int> getQuestionCount() const;

            [[nodiscard]]
            std::vector<QuestionData> getQuestions(int gamemode, int count) const;
        private:
            // DuckDB C API handles
            duckdb_database db_ = nullptr;
            duckdb_connection conn_ = nullptr;

            ~Database();

            static constexpr auto EXCEL_FILE = "question_data.xlsx";
    };

}

#endif