#include "mainwidget.hpp"
#include "outrowidget.hpp"
#include <QJsonObject>

MainWidget::MainWidget(const QSqlDatabase& database, QWidget* parent) : QStackedWidget(parent), database_(database){
    query_ = QSqlQuery(database_);
    query_.exec("SELECT COUNT(*) FROM QuestionData");
    query_.next();
    totalQuantity = query_.value(0).toInt();

    displayQuantity = 0;

    management_ = nullptr;

    bool defaultMuted = false, jsonFileAccessed = false;

    if (QFile file("config.json");
        file.open(QFile::ReadOnly | QFile::Text)
    ) {
        json_ = QJsonDocument::fromJson(file.readAll());
        displayQuantity = json_["display_quantity"].toInt();
        defaultMuted = json_["toggle_default_mute_background"].toBool();
        jsonFileAccessed = true;
    }

    intro_ = new IntroWidget(defaultMuted);
    rule_ = new RuleWidget;

    this->addWidget(intro_);
    this->addWidget(rule_);
    this->setCurrentIndex(0);

    if (!jsonFileAccessed) intro_->blockStart();

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

void MainWidget::outroCall(const Result result, const bool currentMuted, const std::vector<int64_t>& timestamps) {
    const auto outro_ = new OutroWidget(result, currentMuted, timestamps);
    outro_->resize(management_->size());
    management_->close();

    connect(outro_, &OutroWidget::replay, this, [this, outro_] (const bool isMuted) {
        management_ = new ManagementWidget(database_, json_, isMuted);
        outro_->close();
        management_->show();
        management_->setFixedSize(outro_->size());
        connect(management_, &ManagementWidget::finish, this, &MainWidget::outroCall);
    });

    delete management_;
    management_ = nullptr;
    outro_->show();
}
