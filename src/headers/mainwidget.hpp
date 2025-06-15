#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QFile>
#include <QStackedWidget>

#include "introwidget.hpp"
#include "rulewidget.hpp"

class MainWidget final : public QStackedWidget {
    Q_OBJECT
    public:
        explicit MainWidget(const QSqlDatabase& database, QWidget* parent = nullptr);
        ~MainWidget() override;
    private:
        QSqlDatabase database_;
        QSqlQuery query_;
        QJsonDocument json_;

        //  Subwidgets
        IntroWidget* intro_;
        RuleWidget* rule_;

        //  App information
        int totalQuantity, displayQuantity;
};

#endif