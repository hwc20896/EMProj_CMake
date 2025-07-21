#include "utilities/fileread.hpp"

std::expected<QString, FileRead::FileReadError> FileRead::getStyleFromURI(const QString& uri) {
    QFile file(uri);
    if (!file.exists()) {
        return std::unexpected(FileReadError::FileNotFound);
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return std::unexpected(FileReadError::ReadError);
    }

    QString content = file.readAll();
    file.close();

    return content;
}

std::expected<GameConfig, FileRead::FileReadError> FileRead::readGameConfig(const QString& uri) {
    QFile file(uri);
    if (!file.exists()) {
        return std::unexpected(FileReadError::FileNotFound);
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return std::unexpected(FileReadError::ReadError);
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        return std::unexpected(FileReadError::ContentError);
    }

    GameConfig config(
        jsonDoc["display_quantity"].toInt(),
        jsonDoc["app_name"].toString(),
        jsonDoc["toggle_default_mute_background"].toBool(),
        jsonDoc["toggle_default_mute_effect"].toBool()
    );

    return config;
}