#include "elements/optionbutton.hpp"
#include "widgets/templatewidget.hpp"

#define REFRESH_STYLE this->setStyle({})

OptionButton::OptionButton(const QString& optionText, const int mode, QWidget* parent) : QPushButton(optionText, parent) {
    this->setProperty("has_answered", false);

    QString color = "#000000"; // Default black
    if (mode == 1) {
        if (optionText == "是") color = "#008000"; // Green for True
        else if (optionText == "否") color = "#FF0000"; // Red for False
    }

    this->setStyleSheet(QString(STYLESHEET).arg(color));

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