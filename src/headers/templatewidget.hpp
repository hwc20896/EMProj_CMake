#pragma once
#ifndef TEMPLATEWIDGET_HPP
#define TEMPLATEWIDGET_HPP
#include <map>
#include <QJsonArray>
#include <QStringList>
#include <random>
#include <utility>
#include <QSoundEffect>

#include "ui_template.h"
#include "elements/optionbutton.hpp"

#define COLOR(target,color) "<font color="#color">"#target"</font>"

struct QuestionData {
    QString questionTitle_;
    QStringList options_;
    int correctOption_;
    int questionType_; // -1 預設, 0 所有, 1 憲法, 2 基本法
    explicit QuestionData(QString questionTitle, QStringList options, const int correctOption, const int questionType = -1)
        : questionTitle_(std::move(questionTitle)), options_(std::move(options)), correctOption_(correctOption), questionType_(questionType) {}
    explicit QuestionData(const QString& questionTitle, const QString& optionText, const int correctOption, const int questionType = -1)
        : QuestionData(questionTitle, QJsonValue::fromJson(optionText.toUtf8()).toVariant().toStringList(), correctOption, questionType) {}
};

class QuestionWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit QuestionWidget(QuestionData&& question, int index, const std::mt19937& mt, QWidget* parent = nullptr);
        ~QuestionWidget() override;

        /**
         *   @brief Suspend (msec) milliseconds, on another thread.
         *   @param msec Milliseconds you want to suspend.
         */
        static void cooldown(int msec);

        void setEffectMuted(bool muted) const;
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

        //  Sound Effects
        QSoundEffect* correctSound_, * incorrectSound_;

        //  Engine
        std::mt19937 mt_;
    signals:
        void timeTap();
        void score(bool isCorrect);
};

#endif
