#include "mainwidget.hpp"

MainWidget::MainWidget(const QSqlDatabase& database, QWidget* parent) : QStackedWidget(parent), database_(database){
    query_ = QSqlQuery(database_);
    query_.exec("SELECT COUNT(*) FROM QuestionData");
    query_.next();
    totalQuantity = query_.value(0).toInt();

    intro_ = new IntroWidget;
    rule_ = new RuleWidget;
    displayQuantity = 0;

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
        //  ...
    });
}

MainWidget::~MainWidget() {
    delete intro_;
    delete rule_;
}