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
#include <random>

#include "elements/muteswitch.hpp"
#include "utilities/fileread.hpp"
#include "utilities/defines.hpp"
#include "templatewidget.hpp"
#include "result.hpp"
#include "ui_managementwidget.h"

class ManagementWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit ManagementWidget(const QSqlDatabase& database, const GameConfig& config, bool currentMuted, QWidget* parent = nullptr);
        ~ManagementWidget() override;

        void setSoundEffectMuted(bool muted) const;
    private:
        Ui::ManagementWidget* ui_;
        MuteSwitch* muteSwitch_;
        QStackedLayout* stackLayout_;
        QLabel* backgroundImage_;

        //  Query engine
        QSqlDatabase database_;
        QSqlQuery query_;

        //  Engines
        std::random_device device_;
        std::mt19937 mt_;

        //  Question Data
        std::expected<void, FileRead::FileReadError> getQuestions();
        std::vector<QuestionData> questions_;
        std::vector<QuestionWidget*> pages_;
        Result result_;
        int incorrectCount = 0;

        //  Navigation use
        std::vector<bool> pageFinished;
        void updatePages() const;
        void setScore(int correct, int incorrect) const;
        void setProgress(int current, int total) const;

        //  Configs
        GameConfig config_;
        int totalQuantity;

        //  Timers
        std::vector<int64_t> timeStamps;
        std::chrono::time_point<std::chrono::system_clock> start_, end_;

        //  Background music
        bool currentMuted_ = false;
        QAudioOutput* audioOutput_;
        QMediaPlayer* player_;
    signals:
        void finish(Result result, bool currentMuted, const std::vector<int64_t>& timestamps);
};

#endif
