#include "widget_containers/managementwidget.hpp"

#include <ranges>
#include <utility>
#include "utilities/fileread.hpp"
#include "utilities/database.hpp"

ManagementWidget::ManagementWidget(GameConfig config, const int gamemode, const bool currentMuted, QWidget* parent)
: QWidget(parent), ui_(new Ui::ManagementWidget), mt_(device_()), config_(std::move(config)) {
    ui_->setupUi(this);
    stackLayout_ = new QStackedLayout(this);

    //  Get Question Data
    result_ = {.total = config_.displayQuantity};

    this->questions_ = Data::database.getQuestions(gamemode, config_.displayQuantity);

    //  Sound Effects
    correctSound = new QSoundEffect;
    correctSound->setSource({"qrc:/SoundEffects/sounds/bingo.wav"});

    incorrectSound = new QSoundEffect;
    incorrectSound->setSource({"qrc:/SoundEffects/sounds/ohno.wav"});

    pageFinished = std::vector(questions_.size(), false);
    LOG("Pending questions:");
    for (const auto& [index, data] : std::views::enumerate(questions_)) {
        const auto widget = new QuestionWidget(data, index + 1, mt_, this);
        LOG(std::format("[{}]: {}", index + 1, data.getInfo()));
        stackLayout_->addWidget(widget);
        pages_.push_back(widget);

        //  Time recorder for total time and time per question use
        connect(widget, &QuestionWidget::timeTap, this, [this] {
            end_ = std::chrono::high_resolution_clock::now();
            timeStamps.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count());
        });

        connect(widget, &QuestionWidget::playCorrect, this, [this] {
            correctSound->play();
            result_.correct++;
        });

        connect(widget, &QuestionWidget::playIncorrect, this, [this] {
            incorrectSound->play();
            incorrectCount++;
        });

        //  Next Page Button Controller
        connect(widget, &QuestionWidget::enableNextPage, this, [this, index] {
            pageFinished[index] = true;
            ui_->nextQuestion->setEnabled(true);
            this->updatePages();
        });
    }

    //   Navigations
    stackLayout_->setCurrentIndex(0);
    this->updatePages();
    connect(stackLayout_, &QStackedLayout::currentChanged, this, [this] (const int index) {
        ui_->prevQuestion->setVisible(index != 0);
        ui_->nextQuestion->setText(index < result_.total-1? "下一頁 →": "完成");
        ui_->nextQuestion->setEnabled(pageFinished[index]);
    });
    connect(ui_->prevQuestion, &QPushButton::clicked, this, [this] {stackLayout_->setCurrentIndex(stackLayout_->currentIndex() - 1);});
    connect(ui_->nextQuestion, &QPushButton::clicked, this, [this] {
        if (const auto current = stackLayout_->currentIndex(); current < result_.total - 1) {
            stackLayout_->setCurrentIndex(current + 1);
            start_ = std::chrono::high_resolution_clock::now();
        }
        else emit finish(result_, muteSwitch_->getMutedState(), timeStamps);
    });
    ui_->prevQuestion->hide();
    start_ = std::chrono::high_resolution_clock::now();

    //  BGM
    audioOutput_ = new QAudioOutput(this);
    audioOutput_->setVolume(0.15f);
    audioOutput_->setMuted(currentMuted);

    player_ = new QMediaPlayer(this);
    player_->setAudioOutput(audioOutput_);
    player_->setSource({"qrc:/BGM/sounds/OMFG_Pizza.mp3"});
    player_->setLoops(QMediaPlayer::Infinite);
    player_->play();

    //  Mute switch
    currentMuted_ = currentMuted;
    muteSwitch_ = new MuteSwitch({50,50}, currentMuted_, this);
    muteSwitch_->setGeometry(570,10,60,60);
    connect(muteSwitch_, &MuteSwitch::mutedStateChanged, this, [this] (const bool currentState) {
        currentMuted_ = currentState;
        audioOutput_->setMuted(currentMuted_);
    });

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
    for (const auto& page : pages_) {
        delete page;
    }
    delete ui_;
    delete muteSwitch_;
}

void ManagementWidget::updatePages() const {
    setScore(result_.correct, incorrectCount);
    setProgress(result_.correct + incorrectCount, result_.total);
}

void ManagementWidget::setScore(const int correct, const int incorrect) const {
    ui_->corrCount->setText(QString(COLOR(錯誤數 %1,"#ff0000")" | " COLOR(%2 正確數,"#00dd12")).arg(QString::number(incorrect), QString::number(correct)));
}

void ManagementWidget::setProgress(const int current, const int total) const {
    ui_->progress->setText(QString("進度：%1 / %2 - %3%").arg(QString::number(current), QString::number(total), QString::number(current*100.0/total)));
}

void ManagementWidget::setSoundEffectMuted(const bool muted) const {
    correctSound->setMuted(muted);
    incorrectSound->setMuted(muted);
}
