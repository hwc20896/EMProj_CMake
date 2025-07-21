#pragma once
#ifndef FILEREAD_HPP
#define FILEREAD_HPP
#include <QFile>
#include <expected>

#include <QMessageBox>
#include <QApplication>
#include <QJsonObject>
#define THROW_FILE_READ_CRITICAL(code) \
    switch (code){\
        case FileRead::FileReadError::FileNotFound: \
            QMessageBox::critical(nullptr, "File Not Found", "The specified file could not be found."); \
            break; \
        case FileRead::FileReadError::ReadError: \
            QMessageBox::critical(nullptr, "Read Error", "An error occurred while reading the file."); \
            break; \
        case FileRead::FileReadError::UnknownError: \
            QMessageBox::critical(nullptr, "Unknown Error", "An unknown error occurred while accessing the file."); \
            break; \
    }\
    qApp->exit(static_cast<int>(code))

struct GameConfig {
    int displayQuantity;
    QString appName;
    bool defaultBackgroundMuted;
    bool defaultEffectMuted;
    explicit GameConfig(const int displayQuantity = 0, QString appName = "EMProj_CMake", const bool defaultBackgroundMuted = false, const bool defaultEffectMuted = false)
        : displayQuantity(displayQuantity), appName(std::move(appName)), defaultBackgroundMuted(defaultBackgroundMuted), defaultEffectMuted(defaultEffectMuted) {}
};

namespace FileRead {
    // Error codes for file reading operations
    enum class FileReadError: int {
        FileNotFound = 6,
        ReadError = 7,
        ContentError = 8,
        UnknownError = -1
    };

    /**
     *   @brief Style retrieval from file (css).
     *   @param uri File address.
     *   @return The content form the file.
    */
    std::expected<QString, FileReadError> getStyleFromURI(const QString& uri);

    /**
     *   @brief Read the game configuration from a JSON file.
     *   @param uri File address.
     *   @return The GameConfig object containing the configuration data.
     */
    std::expected<GameConfig, FileReadError> readGameConfig(const QString& uri);
}

#endif
