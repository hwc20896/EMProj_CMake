#include "utilities/fileread.hpp"
#include "utilities/defines.hpp"

#include <QJsonValue>

std::expected<QString, FileRead::FileReadError> FileRead::getStyleFromURI(const QString& uri) {
    QFile file(uri);
    if (!file.exists()) {
        ERROR("Cannot find file at " << uri.toStdString());
        return std::unexpected(FileReadError(Error::FileNotFound, "File not found at the specified URI: " + uri));
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ERROR("Cannot open file at " << uri.toStdString());
        return std::unexpected(FileReadError(Error::ReadError, "Failed to open file at the specified URI: " + uri));
    }

    QString content = file.readAll();
    file.close();

    return content;
}

std::expected<GameConfig, FileRead::FileReadError> FileRead::readGameConfig(const QString& uri) {
    QFile file(uri);
    if (!file.exists()) {
        ERROR("Cannot find config JSON file at " << uri.toStdString());
        return std::unexpected(FileReadError(Error::FileNotFound,
                                             "Config JSON file not found at the specified URI: " + uri));
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ERROR("Cannot open config JSON file at " << uri.toStdString());
        return std::unexpected(FileReadError(Error::ReadError,
                                             "Failed to open config JSON file at the specified URI: " + uri));
    }

    const QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        ERROR("Unable to parse config JSON file at " << uri.toStdString());
        return std::unexpected(FileReadError(Error::ContentError,
                                             "Invalid JSON content in the config file at: " + uri));
    }

    GameConfig config(
        jsonDoc["display_quantity"].toInt(),
        jsonDoc["app_name"].toString(),
        jsonDoc["toggle_default_mute_background"].toBool(),
        jsonDoc["toggle_default_mute_effect"].toBool()
    );

    return config;
}