#include "managementwidget.hpp"

#include <ranges>
#include "utilities/fileread.hpp"

ManagementWidget::ManagementWidget(const QSqlDatabase& database, const GameConfig& config, const bool currentMuted, QWidget* parent)
: QWidget(parent), ui_(new Ui::ManagementWidget), config_(config), database_(database), mt_(device_()) {
    ui_->setupUi(this);
    stackLayout_ = new QStackedLayout(this);

    //  Get Question Data
    if (!database_.isOpen()) database_.open();
    query_ = QSqlQuery(database);
    query_.exec("SELECT COUNT(*) FROM QuestionData");
    query_.next();
    totalQuantity = query_.value(0).toInt();
    result_ = {.total = config_.displayQuantity};

    this->getQuestions().or_else([](const FileRead::FileReadError& error) -> std::expected<void, FileRead::FileReadError> {
        THROW_FILE_CRITICAL(error.code, error.message.toStdString());
        return std::unexpected(error);
    });

    pageFinished = std::vector(questions_.size(), false);
    LOG("Pending questions:");
    for (const auto& [index, data] : std::views::enumerate(questions_)) {
        const auto widget = new QuestionWidget(data, index + 1, mt_, this);
        LOG("[" << index+1 << "] " << data.getInfo());
        stackLayout_->addWidget(widget);
        pages_.push_back(widget);

        //  Time recorder for total time and time per question use
        connect(widget, &QuestionWidget::timeTap, this, [this] {
            end_ = std::chrono::high_resolution_clock::now();
            timeStamps.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count());
        });

        //  Score recorder
        connect(widget, &QuestionWidget::score, this, [this, index](const bool isCorrect) {
            pageFinished[index] = true;
            isCorrect? result_.correct++ : incorrectCount++;
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
    database_.close();
    for (const auto& page : pages_) {
        delete page;
    }
    delete ui_;
    delete muteSwitch_;
}

std::expected<void, FileRead::FileReadError> ManagementWidget::getQuestions() {
    std::vector<int> idPool, sampled;
    query_.exec("SELECT ID FROM QuestionData");
    while (query_.next()) idPool.push_back(query_.value("ID").toInt());

    std::ranges::sample(idPool, std::back_inserter(sampled), result_.total, mt_);
    for (const auto& id : sampled) {
        query_.prepare("SELECT * FROM QuestionData WHERE ID = ?");
        query_.addBindValue(id);
        query_.exec();
        if (!query_.next()) {
            return std::unexpected(FileRead::FileReadError(FileRead::Error::ContentError,
                                                           "Failed to retrieve question data for ID: " +
                                                           QString::number(id)));
        }

        const auto questionTitle = query_.value("QuestionTitle").toString();
        const auto options = query_.value("Options").toString();
        const auto correctOption = query_.value("CorrectOption").toInt();

        questions_.emplace_back(questionTitle, options, correctOption);
    }
    return {};
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
    for (const auto& page : pages_) {
        page->setEffectMuted(muted);
    }
}
