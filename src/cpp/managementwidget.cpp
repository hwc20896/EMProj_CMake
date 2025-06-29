#include "managementwidget.hpp"

#include <random>
#include <ranges>

ManagementWidget::ManagementWidget(const QSqlDatabase& database, const QJsonDocument& json, const bool currentMuted, QWidget* parent)
: QWidget(parent), ui_(new Ui::ManagementWidget), json_(json), database_(database) {
    ui_->setupUi(this);
    stackLayout_ = new QStackedLayout(this);

    //  Get Question Data
    if (!database_.isOpen()) database_.open();
    query_ = QSqlQuery(database);
    query_.exec("SELECT COUNT(*) FROM QuestionData");
    query_.next();
    totalQuantity = query_.value(0).toInt();
    result_ = {.total = json_["display_quantity"].toInt()};

    this->getQuestions();

    pageFinished = std::vector(questions_.size(), false);
    for (auto&& [index, data] : std::views::enumerate(questions_)) {
        const auto widget = new QuestionWidget(std::move(data), index + 1);
        stackLayout_->addWidget(widget);

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
        if (const auto current = stackLayout_->currentIndex(); current < displayQuantity-1 ) {
            stackLayout_->setCurrentIndex(current + 1);
            start_ = std::chrono::high_resolution_clock::now();
        }
        else emit finish(result_, muteSwitch_->getMutedState(), timeStamps);
    });
    ui_->prevQuestion->hide();

    //  BGM
    audioOutput_ = new QAudioOutput(this);
    audioOutput_->setVolume(0.15f);
    audioOutput_->setMuted(currentMuted);

    player_ = new QMediaPlayer(this);
    player_->setAudioOutput(audioOutput_);
    player_->setSource({"qrc:/BGM/sounds/OMFG_Pizza.mp3"});
    player_->setLoops(QMediaPlayer::Infinite);

    //  Mute switch
    currentMuted_ = currentMuted;
    muteSwitch_ = new MuteSwitch({50,50}, currentMuted_);
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
    this->setStyleSheet(QuestionWidget::getStyleFromURI(":/CSS/src/css/questioning.css"));
}

ManagementWidget::~ManagementWidget() {
    delete ui_;
    delete muteSwitch_;
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

void ManagementWidget::updatePages() const {
    setScore(result_.correct, incorrectCount);
    setProgress(result_.correct + incorrectCount, result_.total);
}

void ManagementWidget::setScore(const int correct, const int incorrect) const {
    ui_->corrCount->setText(QString(COLOR(錯誤數 %1,"#ff0000")" | " COLOR(%2 正確數,"#00dd12")).arg(QString::number(incorrect), QString::number(correct)));
}

void ManagementWidget::setProgress(const int current, const int total) const {
    ui_->progress->setText(QString("進度：%1 / %2 - %3%").arg(QString::number(current), QString::number(total), QString::number(current*100.0/total,'g',1)));
}
