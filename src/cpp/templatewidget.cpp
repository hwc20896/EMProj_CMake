#include "templatewidget.hpp"
#include <ranges>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include "utilities/fileread.hpp"
#include "utilities/defines.hpp"

QuestionWidget::QuestionWidget(const QuestionData& question, const int index, const std::mt19937& mt, QWidget* parent)
: QWidget(parent), ui_(new Ui::TemplateWidget), question_(question), mt_(mt) {
    ui_->setupUi(this);

    correctText = question_.options_[question_.correctOption_];
    std::ranges::shuffle(question_.options_, mt_);

    //  Title
    ui_->questionTitle->setText(QString("%1: %2").arg(QString::number(index), question_.questionTitle_));

    //  Option buttons
    std::vector<QRect> optionLocations;
    switch (question_.options_.size()){
        case 4:
            optionLocations = {
                {170, 146, 300, 140},
                {530, 146, 300, 140},
                {170, 325, 300, 140},
                {530, 325, 300, 140}
            };
            break;
        case 2:
            optionLocations = {
                {170, 216, 300, 140},
                {530, 216, 300, 140}
            };
            break;
        default:
            WARNING("Unable to determine option button locations. Layout may cause issues.");
            optionLocations = {};
            break;
    }

    for (const auto& [text, location] : std::views::zip(question_.options_, optionLocations)) {
        const auto button = new OptionButton(text, this);
        button->setGeometry(location);
        connect(button, &OptionButton::clicked, this, [this, button] { answerButtonClicked(button); });
        bindToButton.emplace(text, button);
        options_.push_back(button);
    }

    hasAnswered = false;

    //  Sound effects
    correctSound_ = new QSoundEffect;
    correctSound_->setSource({"qrc:/SoundEffects/sounds/bingo.wav"});

    incorrectSound_ = new QSoundEffect;
    incorrectSound_->setSource({"qrc:/SoundEffects/sounds/ohno.wav"});

    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/questioning.css").value_or(""));
}

QuestionWidget::~QuestionWidget() {
    delete ui_;
}

void QuestionWidget::cooldown(const int msec) {
    QEventLoop lp;
    QTimer::singleShot(msec, &lp, &QEventLoop::quit);
    lp.exec();
}

void QuestionWidget::setEffectMuted(const bool muted) const {
    correctSound_->setMuted(muted);
    incorrectSound_->setMuted(muted);
}

void QuestionWidget::answerButtonClicked(OptionButton* button) {
    if (!hasAnswered) {
        hasAnswered = true;
        for (const auto& i: options_) i->setHasAnswered();
        button->setSelected();
        emit timeTap();
        cooldown(800);
        const bool isCorrect = button->text() == correctText;
        if (isCorrect) {
            button->setCorrect(true);
            correctSound_->play();
        } else {
            button->setCorrect(false);
            incorrectSound_->play();
            cooldown(500);
            bindToButton[correctText]->setCorrect(true);
        }
        cooldown(700);
        emit score(isCorrect);
    }
}
