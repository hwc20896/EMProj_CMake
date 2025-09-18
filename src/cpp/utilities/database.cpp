#include "utilities/database.hpp"

#include <string>

int Data::Database::getTotalQuestionCount() {
    int count = 0;
    db_ << "SELECT COUNT(*) FROM QuestionData;" >> count;
    return count;
}

std::vector<QuestionData> Data::Database::getQuestions(const int gamemode, const int count) {
    std::vector<QuestionData> questions;

    /*  queryStr conditions:
     *      mode 0: all questions -> SELECT * FROM QuestionData;                        22x
     *      mode 1: only 憲法 -> SELECT * FROM QuestionData WHERE QuestionType = 0;      9x
     *      mode 2: only 基本法 -> SELECT * FROM QuestionData WHERE QuestionType = 1;    13x
     *      default = mode 0;
     */
    std::string queryStr = "SELECT * FROM QuestionData";
    if (gamemode == 1) queryStr += " WHERE QuestionType = 0";
    else if (gamemode == 2) queryStr += " WHERE QuestionType = 1";
    queryStr += " order by random() limit ?";

    db_ << queryStr << count >> [&](const int id, const std::string& questionTitle, const std::string& options, const int correctOption, const int questionType) {
        questions.emplace_back(id, QString::fromStdString(questionTitle), QString::fromStdString(options), correctOption, questionType);
    };
    return questions;
}
