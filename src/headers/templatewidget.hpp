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

#define RANDOM_ALGORITHM std::mt19937(std::random_device()())
#define COLOR(target,color) "<font color="#color">"#target"</font>"

struct QuestionData {
    QString questionTitle_;
    QStringList options_;
    int correctOption_;
    int questionType_; // -1 預設, 0 憲法, 1 基本法
    explicit QuestionData(QString questionTitle, QStringList options, const int correctOption, const int questionType = -1)
        : questionTitle_(std::move(questionTitle)), options_(std::move(options)), correctOption_(correctOption), questionType_(questionType) {}
    explicit QuestionData(const QString& questionTitle, const QString& optionText, const int correctOption, const int questionType = -1)
        : QuestionData(questionTitle, QJsonValue::fromJson(optionText.toUtf8()).toVariant().toStringList(), correctOption, questionType) {}
};

class QuestionWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit QuestionWidget(QuestionData&& question, int index, QWidget* parent = nullptr);
        ~QuestionWidget() override;

        /**
         *   @brief Style retrieval from file (css).
         *   @param uri File address.
         *   @return The content form the file.
         */
        static QString getStyleFromURI(const QString& uri);

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
    signals:
        void timeTap();
        void score(bool isCorrect);
};

#endif
