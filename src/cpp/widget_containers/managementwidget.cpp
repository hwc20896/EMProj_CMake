#include "widget_containers/managementwidget.hpp"
#include "utilities/fileread.hpp"
#include "backends/database.hpp"

#include <ranges>
#include <utility>
#include <future>

#include "ui_managementwidget.h"
#include "backends/audios.hpp"
#include "backends/questionbackend.hpp"

using EMProj_CMake_Backend::audio_, EMProj_CMake_Backend::scorer_;

ManagementWidget::ManagementWidget(GameConfig config, const int gamemode, const bool currentMuted, QWidget* parent)
: QWidget(parent), ui_(new Ui::ManagementWidget), mt_(device_()), config_(std::move(config)) {
    ui_->setupUi(this);
    stackLayout_ = new QStackedLayout(this);

    scorer_.loadQuestion(gamemode, config_.displayQuantity);

    //  Get Question Data
    LOG("Pending questions:");
    for (const auto i: std::views::iota(0, config_.displayQuantity)) {
        const auto widget = new QuestionWidget(scorer_[i], i + 1, mt_, this);
        LOG(std::format("[{}]: {}", i + 1, scorer_[i].getInfo()));
        pages_.push_back(widget);
        stackLayout_->addWidget(widget);

        connect(widget, &QuestionWidget::answerButtonClicked, this, [this, widget, i](OptionButton* button) {
            if (scorer_.checkQuestion(button->text(), i)) {
                widget->setCorrect();
            } else {
                widget->setIncorrect(button);
            }
            ui_->nextQuestion->setEnabled(true);
            updatePages();
        });
    }

    //  Navigation buttons
    stackLayout_->setCurrentIndex(0);
    ui_->prevQuestion->hide();
    ui_->nextQuestion->setEnabled(false);
    this->updatePages();
    connect(stackLayout_, &QStackedLayout::currentChanged, this, [this](const int index) {
        ui_->prevQuestion->setVisible(index != 0);
        if (index == config_.displayQuantity - 1) {
            ui_->nextQuestion->setText("完成");
            ui_->nextQuestion->setEnabled(scorer_.getAnsweredCount() == config_.displayQuantity);
        } else {
            ui_->nextQuestion->setText("下一題 →");
            ui_->nextQuestion->setEnabled(scorer_.getAnsweredCount() > index);
        }
    });
    connect(ui_->prevQuestion, &QPushButton::clicked, this, [this] {
        if (const auto currentIndex = stackLayout_->currentIndex(); currentIndex > 0) {
            stackLayout_->setCurrentIndex(currentIndex);
        }
    });
    connect(ui_->nextQuestion, &QPushButton::clicked, this, [this] {
        if (const auto currentIndex = stackLayout_->currentIndex();
            currentIndex < config_.displayQuantity - 1)
        {
            scorer_.startTimer();
            stackLayout_->setCurrentIndex(currentIndex + 1);
        } else {
            //  Finish
            emit finish(scorer_.getScore(), muteSwitch_->getMutedState(), scorer_.getTotalTime());
        }
    });
    scorer_.startTimer();

    //  BGM
    audio_.playBackgroundMusic();

    //  Mute switch
    muteSwitch_ = new MuteSwitch({50,50}, currentMuted, this);
    muteSwitch_->setGeometry(570,10,60,60);

    //  Question layout
    ui_->optionWidget->setLayout(stackLayout_);

    //  Background image
    backgroundImage_ = new QLabel(this);
    backgroundImage_->setPixmap({":/BackgroundImages/backgrounds/qnabg.png"});
    backgroundImage_->setGeometry(0,0,1000,700);
    backgroundImage_->lower();

    //  Styles
    ui_->prevQuestion->setObjectName("navigator");
    ui_->nextQuestion->setObjectName("navigator");
    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/questioning.css").value_or(""));
}

ManagementWidget::~ManagementWidget() {
    audio_.stopBackgroundMusic();
    for (const auto& page : pages_) {
        delete page;
    }
    delete ui_;
    delete muteSwitch_;
}

void ManagementWidget::updatePages() const {
    setScore(scorer_.getScore());
    setProgress(scorer_.getAnsweredCount(), config_.displayQuantity);
}

void ManagementWidget::setScore(const std::tuple<int, int>& score) const {
    ui_->corrCount->setText(QString(COLOR(錯誤數 %1,"#ff0000")" | " COLOR(%2 正確數,"#00dd12")).arg(QString::number(std::get<1>(score)), QString::number(std::get<0>(score))));
}

void ManagementWidget::setProgress(const int current, const int total) const {
    ui_->progress->setText(QString("進度：%1 / %2 - %3%").arg(QString::number(current), QString::number(total), QString::number(current*100.0/total)));
}

void ManagementWidget::setSoundEffectMuted(const bool muted) {
    audio_.setEffectMuted(muted);
}
