#include "templatewidget.hpp"
#include <QFile>
#include <ranges>
#include <array>
#include <QEventLoop>
#include <QTimer>

#define SET_OPTION_PROPERTY(button, value)\
        button->setProperty("answer_status", value); \
        button->setStyle({})

QuestionWidget::QuestionWidget(QuestionData&& question, const int index, QWidget* parent)
: QWidget(parent), ui_(new Ui::TemplateWidget), question_(std::move(question)) {
    ui_->setupUi(this);

    correctText = question_.options_[question_.correctOption_];
    std::ranges::shuffle(question_.options_, RANDOM_ALGORITHM);

    //  Title
    ui_->questionTitle->setText(QString("%1: %2").arg(QString::number(index), question_.questionTitle_));

    for (const auto& button : optionButtons) button->setVisible(false);
    for (const auto& [text, button] : std::views::zip(question_.options_, optionButtons)) {
        button->setObjectName("option");
        button->setProperty("has_answered", "false");
        bindToButton.emplace(text, button);
        button->setText(text);
        button->setVisible(true);
        connect(button, &QPushButton::clicked, this, [this, &button]{this->answerButtonClicked(button);});
    }
    hasAnswered = false;

    //  Sound effects
    correctSound_ = new QSoundEffect;
    correctSound_->setSource({"qrc:/SoundEffects/sounds/bingo.wav"});

    incorrectSound_ = new QSoundEffect;
    incorrectSound_->setSource({"qrc:/SoundEffects/sounds/ohno.wav"});

    this->setStyleSheet(getStyleFromURI(":/CSS/src/css/questioning.css"));
}

QuestionWidget::~QuestionWidget() {
    delete ui_;
}

QString QuestionWidget::getStyleFromURI(const QString& uri) {
    if (QFile file(uri); file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString result = file.readAll();
        file.close();
        return result;
    }
    return "";
}

void QuestionWidget::answerButtonClicked(QPushButton* button) {
    if (!hasAnswered) {
        hasAnswered = true;
        for (const auto& _button : optionButtons) _button->setProperty("has_answered", "true");
        emit timeTap();
        SET_OPTION_PROPERTY(button, "chosen");
        const bool isCorrect = button->text() == this->correctText;
        cooldown(800);
        if (isCorrect) {
            SET_OPTION_PROPERTY(button, "correct");
            correctSound_->play();
        }
        else {
            SET_OPTION_PROPERTY(button, "incorrect");
            incorrectSound_->play();
            cooldown(500);
            const auto correctButton = bindToButton[correctText];
            SET_OPTION_PROPERTY(correctButton, "correct");
        }
        cooldown(700);
        emit score(isCorrect);
    }
}

void QuestionWidget::cooldown(const int msec) {
    QEventLoop lp;
    QTimer::singleShot(msec, &lp, &QEventLoop::quit);
    lp.exec();
}
