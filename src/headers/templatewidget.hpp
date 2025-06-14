#pragma once
#ifndef TEMPLATEWIDGET_HPP
#define TEMPLATEWIDGET_HPP
#include <map>
#include <QJsonArray>
#include <QStringList>
#include <QWidget>

struct QuestionData {
    QString questionTitle_;
    QStringList options_;
    int correctOption_;
    explicit QuestionData(const QString& questionTitle, const QStringList& options, const int correctOption)
        : questionTitle_(questionTitle), options_(options), correctOption_(correctOption) {}
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
        QuestionData question_;
};

#endif
