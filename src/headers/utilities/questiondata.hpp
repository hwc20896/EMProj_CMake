#pragma once
#ifndef QUESTIONDATA_HPP
#define QUESTIONDATA_HPP

#include <QJsonValue>

struct QuestionData {
    int id_;
    QString questionTitle_;
    QStringList options_;
    int correctOption_;
    int questionType_; // 0 所有, 1 憲法, 2 基本法
    explicit QuestionData(const int id, QString questionTitle, QStringList options, const int correctOption, const int questionType = 0)
        : id_(id), questionTitle_(std::move(questionTitle)), options_(std::move(options)), correctOption_(correctOption), questionType_(questionType) {}
    explicit QuestionData(const int id, const QString& questionTitle, const QString& optionText, const int correctOption, const int questionType = 0)
        : QuestionData(id, questionTitle, QJsonValue::fromJson(optionText.toUtf8()).toVariant().toStringList(), correctOption, questionType) {}

    [[nodiscard]] std::string getInfo() const {
        return std::format("ID: {:02}, Question Type: {}", id_, questionType_);
    }
};

#endif