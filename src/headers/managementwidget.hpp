#pragma once
#ifndef MANAGEMENTWIDGET_HPP
#define MANAGEMENTWIDGET_HPP
#include "templatewidget.hpp"
#include <QSqlQuery>
#include <QJsonDocument>

#include "ui_managementwidget.h"

class ManagementWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit ManagementWidget(const QSqlDatabase& database, const QJsonDocument& json, QWidget* parent = nullptr);
        ~ManagementWidget() override;
    private:
        Ui::ManagementWidget* ui_;

        //  Query engine
        QJsonDocument json_;
        QSqlDatabase database_;
        QSqlQuery query_;

        //  Question Data
        void getQuestions();
        std::vector<QuestionData> questions_;
        std::vector<QuestionWidget> pages_;

        //  Configs
        int totalQuantity, displayQuantity;
};

#endif
