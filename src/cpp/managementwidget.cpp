#include "managementwidget.hpp"
#include <random>
#include <ranges>

#define RANDOM_ALGORITHM std::mt19937(std::random_device()())

ManagementWidget::ManagementWidget(const QSqlDatabase& database, const QJsonDocument& json, QWidget* parent)
: QWidget(parent), ui_(new Ui::ManagementWidget), json_(json), database_(database) {
    ui_->setupUi(this);
    if (!database_.isOpen()) database_.open();
    query_ = QSqlQuery(database);

    totalQuantity = query_.value(0).toInt();
    displayQuantity = json_["display_quantity"].toInt();

    this->getQuestions();

    for (auto&& [index, data] : std::views::enumerate(questions_)) {

    }
}

ManagementWidget::~ManagementWidget() {
    delete ui_;
}

void ManagementWidget::getQuestions() {
    std::vector<int> idPool, sampled;
    query_.exec("SELECT ID FROM QuestionData");
    while (query_.next()) idPool.push_back(query_.value(0).toInt());

    std::ranges::sample(idPool, std::back_inserter(sampled), displayQuantity, RANDOM_ALGORITHM);
    for (const auto& id : sampled) {
        query_.prepare("SELECT * FROM QuestionData WHERE ID = ?");
        query_.addBindValue(id);
        query_.exec();
        query_.next();

        const auto questionTitle = query_.value("QuestionTitle").toString();
        const auto options = query_.value("Options").toString();
        const auto correctOption = query_.value("CorrectOption").toInt();

        questions_.emplace_back(questionTitle, options, correctOption);
    }
}