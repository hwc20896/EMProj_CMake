#include "mainwidget.hpp"

MainWidget::MainWidget(const QSqlDatabase& database, QWidget* parent) : QStackedWidget(parent), database_(database){
    query_ = QSqlQuery(database_);
    query_.exec("SELECT COUNT(*) FROM QuestionData");
    query_.next();
    totalQuantity = query_.value(0).toInt();

    intro_ = new IntroWidget;
    rule_ = new RuleWidget;
    displayQuantity = 0;

    management_ = nullptr;

    if (QFile file("config.json");
        file.open(QFile::ReadOnly | QFile::Text)
    ) {
        json_ = QJsonDocument::fromJson(file.readAll());
        displayQuantity = json_["display_quantity"].toInt();
    }
    else {
        intro_->blockStart();
    }

    this->addWidget(intro_);
    this->addWidget(rule_);
    this->setCurrentIndex(0);

    connect(intro_, &IntroWidget::toRulePage, this, [this] {
        this->setCurrentIndex(1);
    });
    connect(rule_, &RuleWidget::returnToIntro, this, [this] {
        this->setCurrentIndex(0);
    });

    connect(intro_, &IntroWidget::start, this, [this] {
        management_ = new ManagementWidget(database_, json_, intro_->getMutedState());
        this->close();
        management_->show();
        management_->setFixedSize(this->size());
        connect(management_, &ManagementWidget::finish, this, &MainWidget::outroCall);
    });
}

MainWidget::~MainWidget() {
    delete intro_;
    delete rule_;
}

void MainWidget::outroCall(const int correctCount, const bool currentMuted, const std::vector<int64_t>& timestamps) {
    //  TODO: outro
}
