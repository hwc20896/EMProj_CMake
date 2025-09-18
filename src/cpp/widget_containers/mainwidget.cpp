#include "widget_containers/mainwidget.hpp"
#include "widget_containers/outrowidget.hpp"
#include "utilities/defines.hpp"
#include "utilities/database.hpp"

MainWidget::MainWidget(QWidget* parent) : QStackedWidget(parent) {
    try {
        totalQuantity = Data::database.getTotalQuestionCount();
    }
    catch (const sqlite::errors::error&) {
        ERROR("It seems that the database file is missing or corrupted. The application will now exit.");
        std::exit(-1);
    }

    //  Initializers
    intro_ = new IntroWidget(false);
    rule_ = new RuleWidget;

    currentMode_ = 0;

    //  Json Configs
    std::string blockText;
    const auto fileConfig = FileRead::readGameConfig("config.json").and_then(
        [this](const GameConfig& config) -> std::expected<GameConfig, FileRead::FileReadError> {
            intro_->setMutedState(config.defaultBackgroundMuted);
            LOG("Read config.json successfully.");
            return config;
        }
    ).or_else(
        [this, &blockText](const FileRead::FileReadError&) -> std::expected<GameConfig, FileRead::FileReadError> {
            blockText = BLOCKSTART_TEXT;
            intro_->blockStart();
            ERROR("Unable to read config.json, Start Button disabled.");
            return GameConfig();
        }
    );
    config_ = fileConfig.value();

    rule_->setRuleText(blockText, config_.displayQuantity, this->totalQuantity);
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
        currentMode_ = intro_->getCurrentMode();
        management_ = new ManagementWidget(config_, currentMode_, intro_->getMutedState());
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
    const auto outro_ = new OutroWidget(result, currentMuted, currentMode_, timestamps);
    outro_->setWindowTitle(config_.appName);
    outro_->resize(management_->size());
    management_->close();

    connect(outro_, &OutroWidget::replay, this, [this, outro_] (const bool isMuted) {
        currentMode_ = outro_->getCurrentMode();
        management_ = new ManagementWidget(config_, currentMode_,isMuted);
        management_->setWindowTitle(config_.appName);
        outro_->close();
        LOG("Game restarting!");
        management_->show();
        management_->setFixedSize(outro_->size());
        connect(management_, &ManagementWidget::finish, this, &MainWidget::outroCall);
    });

    delete management_;
    management_ = nullptr;
    outro_->show();
}
