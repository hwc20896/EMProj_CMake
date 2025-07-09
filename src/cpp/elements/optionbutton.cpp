#include "elements/optionbutton.hpp"
#include "templatewidget.hpp"

#define REFRESH_STYLE this->setStyle({})

OptionButton::OptionButton(const QString& optionText, QWidget* parent) : QPushButton(optionText, parent) {
    this->setProperty("has_answered", false);
    this->setStyleSheet(QuestionWidget::getStyleFromURI(":/CSS/src/css/option.css"));

    this->setObjectName("option");
    this->setFont({"Microsoft JhengHei", 15});

    connect(this, &QPushButton::clicked, [this]{emit clicked(this);});
}

void OptionButton::setHasAnswered(){
    this->setProperty("has_answered", true);
    REFRESH_STYLE;
}

void OptionButton::setSelected() {
    this->setProperty("answer_status", "chosen");
    REFRESH_STYLE;
}

void OptionButton::setCorrect(const bool correct) {
    this->setProperty("answer_status", correct ? "correct" : "incorrect");
    REFRESH_STYLE;
}