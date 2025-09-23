#pragma once
#ifndef OPTIONBUTTON_HPP
#define OPTIONBUTTON_HPP
#include <QPushButton>

class OptionButton final : public QPushButton {
    Q_OBJECT
    public:
        explicit OptionButton(const QString& optionText, int mode = 0, QWidget* parent = nullptr);

        //  States
        void setHasAnswered(); // Prevent further interaction
        void setSelected();
        void setCorrect(bool correct);
    signals:
        void clicked(OptionButton* button);
    private:
        static constexpr auto STYLESHEET = R"(
            QPushButton#option{
                background-color: #f0f0f0;
                color: %1;
                border: 1px solid black;
                border-radius: 5px;
            }

            QPushButton#option[has_answered="true"]{
                color: black;
            }

            QPushButton#option:hover[has_answered="false"]{
                background-color: #6161ff;
                color: white;
            }

            /*  Pressed  */
            QPushButton#option[answer_status="chosen"]{
                background-color: #6161ff;
                color: white;
            }

            /*  Option: Correct */
            QPushButton#option[answer_status="correct"]{
                background-color: chartreuse;
            }

            /*  Option: Incorrect  */
            QPushButton#option[answer_status="incorrect"]{
                background-color: red;
            }
        )";
};

#endif