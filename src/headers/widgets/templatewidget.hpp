#pragma once
#ifndef TEMPLATEWIDGET_HPP
#define TEMPLATEWIDGET_HPP
#include <map>
#include <QJsonArray>
#include <QStringList>
#include <random>
#include <utility>
#include <QSoundEffect>
#include <QWidget>

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

        /**
         *   @brief Suspend (msec) milliseconds, on another thread.
         *   @param msec Milliseconds you want to suspend.
         */
        static void cooldown(int msec);
    private:
        Ui::TemplateWidget* ui_;

        //  Question data
        QuestionData question_;
        QString correctText;
        bool hasAnswered;

        //  Button binder
        std::map<QString, OptionButton*> bindToButton;
        std::vector<OptionButton*> options_;

        //  Answer checker
        void answerButtonClicked(OptionButton* button);

        //  Engine
        std::mt19937 mt_;
    signals:
        void timeTap();
        void enableNextPage();

        //  Sound Effect
        void playCorrect();
        void playIncorrect();
};

#endif
