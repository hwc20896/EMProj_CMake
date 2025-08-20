#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QFile>
#include <QStackedWidget>

#include "introwidget.hpp"
#include "rulewidget.hpp"
#include "managementwidget.hpp"
#include "utilities/fileread.hpp"

class MainWidget final : public QStackedWidget {
    Q_OBJECT
    public:
        explicit MainWidget(const QSqlDatabase& database, QWidget* parent = nullptr);
        ~MainWidget() override;
    private:
        QSqlDatabase database_;
        QSqlQuery query_;
        QJsonDocument json_;
        int currentMode_;

        //  Subwidgets
        IntroWidget* intro_;
        RuleWidget* rule_;

        //  App information
        GameConfig config_;
        int totalQuantity;

        //  Main
        ManagementWidget* management_;
    private slots:
        void outroCall(Result result, bool currentMuted, const std::vector<int64_t>& timestamps);
    private:
        static constexpr auto BLOCKSTART_TEXT = "（由於缺失配置文件，此規則無效）";
};

#endif