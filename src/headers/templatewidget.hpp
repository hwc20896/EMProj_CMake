#pragma once
#ifndef TEMPLATEWIDGET_HPP
#define TEMPLATEWIDGET_HPP
#include <map>
#include <QJsonArray>
#include <QStringList>
#include <random>
#include <utility>

#include "ui_template.h"

#define RANDOM_ALGORITHM std::mt19937(std::random_device()())

struct QuestionData {
    QString questionTitle_;
    QStringList options_;
    int correctOption_;
    explicit QuestionData(QString  questionTitle, const QStringList& options, const int correctOption)
        : questionTitle_(std::move(questionTitle)), options_(options), correctOption_(correctOption) {}
    explicit QuestionData(const QString& questionTitle, const QString& optionText, const int correctOption)
        : QuestionData(questionTitle, QJsonValue::fromJson(optionText.toUtf8()).toVariant().toStringList(), correctOption) {}
};

class QuestionWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit QuestionWidget(QuestionData&& question, int index, QWidget* parent = nullptr);
        ~QuestionWidget() override;

        static QString getStyleFromURI(const QString& uri);
    private:
        Ui::TemplateWidget* ui_;

        //  Question data
        QuestionData question_;
        QString correctText;
};

#endif
