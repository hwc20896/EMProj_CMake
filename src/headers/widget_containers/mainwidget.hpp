#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QStackedWidget>

#include "widgets/introwidget.hpp"
#include "widgets/rulewidget.hpp"
#include "managementwidget.hpp"
#include "utilities/fileread.hpp"

class MainWidget final : public QStackedWidget {
    Q_OBJECT
    public:
        explicit MainWidget(QWidget* parent = nullptr);
        ~MainWidget() override;
    private:
        QJsonDocument json_;
        int currentMode_;

        //  Subwidgets
        IntroWidget* intro_;
        RuleWidget* rule_;

        //  App information
        GameConfig config_;

        //  Main
        ManagementWidget* management_;
    private slots:
        void outroCall(const std::tuple<int, int>& result, bool currentMuted, int64_t totalTime);
    private:
        static constexpr auto BLOCKSTART_TEXT = "（由於缺失配置文件，此規則無效）";
};

#endif