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

//  PIMPL pattern
namespace Ui {
    class TemplateWidget;
}

#define COLOR(target,color) "<font color="#color">"#target"</font>"

struct QuestionData {
    int id_;
    QString questionTitle_;
    QStringList options_;
    int correctOption_;
    int questionType_; // 0 所有, 1 憲法, 2 基本法
    explicit QuestionData(const int id, QString questionTitle, QStringList options, const int correctOption, const int questionType = 0)
        : id_(id), questionTitle_(std::move(questionTitle)), options_(std::move(options)), correctOption_(correctOption), questionType_(questionType) {}
    explicit QuestionData(const int id, const QString& questionTitle, const QString& optionText, const int correctOption, const int questionType = 0)
        : QuestionData(id, questionTitle, QJsonValue::fromJson(optionText.toUtf8()).toVariant().toStringList(), correctOption, questionType) {}

    [[nodiscard]] std::string getInfo() const {
        return std::format("ID: {:02}, Question Type: {}", id_, questionType_);
    }
};

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
