#include "backends/database.hpp"

#include <string>

void EMProj_CMake_Backend::Database::testDatabase() {
    [[maybe_unused]] int count;
    db_ << "select count(id) from QuestionData" >> count;
}

int EMProj_CMake_Backend::Database::getQuestionCount(const int gamemode) {
    int count = 0;

    /*  queryStr conditions:
     *      mode 0: all questions -> SELECT COUNT(*) FROM QuestionData;                        22x
     *      mode 1: only 憲法 -> SELECT COUNT(*) FROM QuestionData WHERE QuestionType = 0;      9x
     *      mode 2: only 基本法 -> SELECT COUNT(*) FROM QuestionData WHERE QuestionType = 1;    13x
     *      default = mode 0;
     */
    std::string queryStr = "SELECT COUNT(*) FROM QuestionData";
    if (gamemode == 1) queryStr += " WHERE QuestionType = 0";
    else if (gamemode == 2) queryStr += " WHERE QuestionType = 1";

    db_ << queryStr >> count;
    return count;
}

std::vector<int> EMProj_CMake_Backend::Database::getQuestionCount() {
    std::vector<int> result;
    db_ << "select QuestionType, count(id) from QuestionData group by QuestionType" >> [&](const int, const int count) {
        result.push_back(count);
    };
    return result;
}

std::vector<QuestionData> EMProj_CMake_Backend::Database::getQuestions(const int gamemode, const int count) {
    std::vector<QuestionData> questions;

    //  See getQuestionCount() for queryStr conditions
    std::string queryStr = "SELECT * FROM QuestionData";
    if (gamemode == 1) queryStr += " WHERE QuestionType = 0";
    else if (gamemode == 2) queryStr += " WHERE QuestionType = 1";
    queryStr += " order by random() limit ?";

    db_ << queryStr << count >> [&](const int id, const std::string& questionTitle, const std::string& options, const int correctOption, const int questionType, const int optionType) {
        questions.emplace_back(id, QString::fromStdString(questionTitle), QString::fromStdString(options), correctOption, questionType, optionType);
    };
    return questions;
}
