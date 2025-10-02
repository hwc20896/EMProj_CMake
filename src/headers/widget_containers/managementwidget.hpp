#pragma once
#ifndef MANAGEMENTWIDGET_HPP
#define MANAGEMENTWIDGET_HPP
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QStackedLayout>
#include <QTimer>
#include <QLabel>
#include <vector>
#include <random>
#include <chrono>
#include <tuple>

#include "elements/muteswitch.hpp"
#include "utilities/fileread.hpp"
#include "utilities/defines.hpp"
#include "widgets/templatewidget.hpp"

//  PIMPL pattern
namespace Ui {
    class ManagementWidget;
}

class ManagementWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit ManagementWidget(GameConfig config, int gamemode, bool currentMuted, QWidget* parent = nullptr);
        ~ManagementWidget() override;

        static void setSoundEffectMuted(bool muted);
    private:
        Ui::ManagementWidget* ui_;
        MuteSwitch* muteSwitch_;
        QStackedLayout* stackLayout_;
        QLabel* backgroundImage_;

        //  Engines
        std::random_device device_;
        std::mt19937 mt_;

        //  Question Data
        std::vector<QuestionWidget*> pages_;

        //  Navigation use
        void updatePages() const;
        void setScore(const std::tuple<int, int>& score) const;
        void setProgress(int current, int total) const;

        //  Configs
        GameConfig config_;
    signals:
        void finish(const std::tuple<int, int>& result, bool currentMuted, int64_t totalTime);
};

#endif
