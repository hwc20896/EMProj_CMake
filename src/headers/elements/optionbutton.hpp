#pragma once
#ifndef OPTIONBUTTON_HPP
#define OPTIONBUTTON_HPP
#include <QPushButton>

class OptionButton final : public QPushButton {
    Q_OBJECT
    public:
        explicit OptionButton(const QString& optionText, QWidget* parent = nullptr);

        //  States
        void setHasAnswered(); // Prevent further interaction
        void setSelected();
        void setCorrect(bool correct);
    signals:
        void clicked(OptionButton* button);
};

#endif