#pragma once
#ifndef FILEREAD_HPP
#define FILEREAD_HPP
#include <QFile>
#include <expected>

struct GameConfig {
    int displayQuantity = 0;
    QString appName = "EMProj_CMake";
    bool defaultBackgroundMuted = false;
    bool defaultEffectMuted = false;
};

namespace FileRead {
    enum class Error: int {
        FileNotFound = 6,
        ReadError = 7,
        ContentError = 8,
        UnknownError = -1
    };
    // Errors for file reading operations
    struct FileReadError {
        Error code;
        QString message;
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
