#pragma once
#ifndef TEMPLATEWIDGET_HPP
#define TEMPLATEWIDGET_HPP
#include <unordered_map>
#include <random>
#include <utility>

#include "elements/optionbutton.hpp"
#include "utilities/questiondata.hpp"

//  PIMPL pattern
namespace Ui {
    class TemplateWidget;
}

#define COLOR(target,color) "<font color="#color">"#target"</font>"

class QuestionWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit QuestionWidget(const QuestionData& question, int index, const std::mt19937& mt, QWidget* parent = nullptr);
        ~QuestionWidget() override;

        /**  @brief Highlight the correct answer.
         */
        void setCorrect() const;

        /**  @brief Highlight the correct answer and mark the clicked button as incorrect.
         *   @param clickedButton The button that was clicked by the user.
         */
        void setIncorrect(OptionButton* clickedButton) const;
    private:
        Ui::TemplateWidget* ui_;

        //  Question data
        QuestionData question_;
        QString correctText;
        bool hasAnswered;

        //  Button binder
        std::unordered_map<QString, OptionButton*> bindToButton;
        std::vector<OptionButton*> options_;

        //  Engine
        std::mt19937 mt_;
    signals:
        //  Answer checker
        void answerButtonClicked(OptionButton* button);
};

#endif
