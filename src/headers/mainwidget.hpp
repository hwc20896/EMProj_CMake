#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QStackedWidget>
#include <QSqlQuery>
#include "introwidget.hpp"
#include "rulewidget.hpp"

class MainWidget final : public QStackedWidget {
    Q_OBJECT
    public:
        explicit MainWidget(const QSqlDatabase& database, QWidget* parent = nullptr);
        ~MainWidget() override;
    private:
        QSqlDatabase database_;

        //  Subwidgets
        IntroWidget* intro_;
        RuleWidget* rule_;
};

#endif