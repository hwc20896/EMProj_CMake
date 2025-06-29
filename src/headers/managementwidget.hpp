#pragma once
#ifndef MANAGEMENTWIDGET_HPP
#define MANAGEMENTWIDGET_HPP
#include <chrono>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QSqlQuery>
#include <QStackedLayout>
#include <QTimer>
#include <vector>

#include "muteswitch.hpp"
#include "templatewidget.hpp"
#include "ui_managementwidget.h"

class ManagementWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit ManagementWidget(const QSqlDatabase& database, const QJsonDocument& json, bool currentMuted, QWidget* parent = nullptr);
        ~ManagementWidget() override;

    private:
        Ui::ManagementWidget* ui_;
        MuteSwitch* muteSwitch_;
        QStackedLayout* stackLayout_;

        //  Query engine
        QJsonDocument json_;
        QSqlDatabase database_;
        QSqlQuery query_;

        //  Question Data
        void getQuestions();
        std::vector<QuestionData> questions_;
        std::vector<QuestionWidget> pages_;
        int correctCount=0, incorrectCount=0;

        //  Navigation use
        std::vector<bool> pageFinished;
        void updatePages() const;
        void setScore(int correct, int incorrect) const;
        void setProgress(int current, int total) const;

        //  Configs
        int totalQuantity, displayQuantity;

        //  Timers
        std::vector<int64_t> timeStamps;
        std::chrono::time_point<std::chrono::system_clock> start_, end_;

        //  Background music
        bool currentMuted_ = false;
        QAudioOutput* audioOutput_;
        QMediaPlayer* player_;
    signals:
        void finish(int correctCount, bool currentMuted, const std::vector<int64_t>& timestamps);
};

#endif
