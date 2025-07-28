#include "mainwidget.hpp"
#include "outrowidget.hpp"
#include "utilities/defines.hpp"

MainWidget::MainWidget(const QSqlDatabase& database, QWidget* parent) : QStackedWidget(parent), database_(database){
    query_ = QSqlQuery(database_);
    query_.exec("SELECT COUNT(*) FROM QuestionData");
    query_.next();
    totalQuantity = query_.value(0).toInt();

    //  Initializers
    intro_ = new IntroWidget(false);
    rule_ = new RuleWidget;

    //  Json Configs
    const auto fileConfig = FileRead::readGameConfig("config.json").and_then(
        [this](const GameConfig& config) -> std::expected<GameConfig, FileRead::FileReadError> {
            intro_->setMutedState(config.defaultBackgroundMuted);
            LOG("Read config.json successfully.");
            return config;
        }
    ).or_else(
        [this](FileRead::FileReadError) -> std::expected<GameConfig, FileRead::FileReadError> {
            intro_->blockStart();
            ERROR("Unable to read config.json, Start Button disabled.");
            return GameConfig();
        }
    );
    config_ = fileConfig.value();

    rule_->setRuleText(config_.displayQuantity, this->totalQuantity);
    management_ = nullptr;

    this->addWidget(intro_);
    this->addWidget(rule_);
    this->setCurrentIndex(0);
    this->setWindowTitle(config_.appName);

    connect(intro_, &IntroWidget::toRulePage, this, [this] {
        this->setCurrentIndex(1);
    });
    connect(rule_, &RuleWidget::returnToIntro, this, [this] {
        this->setCurrentIndex(0);
    });

    connect(intro_, &IntroWidget::start, this, [this] {
        management_ = new ManagementWidget(database_, config_, intro_->getMutedState());
        management_->setWindowTitle(config_.appName);
        management_->setSoundEffectMuted(config_.defaultEffectMuted);
        this->close();
        LOG("Game starting!");
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
    outro_->setWindowTitle(config_.appName);
    outro_->resize(management_->size());
    management_->close();

    connect(outro_, &OutroWidget::replay, this, [this, outro_] (const bool isMuted) {
        management_ = new ManagementWidget(database_, config_, isMuted);
        outro_->close();
        management_->show();
        management_->setFixedSize(outro_->size());
        connect(management_, &ManagementWidget::finish, this, &MainWidget::outroCall);
    });

    delete management_;
    management_ = nullptr;
    outro_->show();
}
