#pragma once
#ifndef DEFINES_HPP
#define DEFINES_HPP

// Log macro
#define LOG(msg) qDebug() << std::format("\033[32m[LOG]\t {}\033[0m", msg)

#define ERROR(msg) qDebug() << std::format("\033[31m[ERROR]\t {}\033[0m", msg)

#define WARNING(msg) qDebug() << std::format("\033[33m[WARNING]\t {}\033[0m", msg)

//  Throw critical
#define THROW_FILE_CRITICAL(code) \
    switch (code){\
        case FileRead::FileReadError::FileNotFound: \
            QMessageBox::critical(nullptr, "無法找到文件", "所需文件不存在。"); \
            break; \
        case FileRead::FileReadError::ReadError: \
            QMessageBox::critical(nullptr, "讀取錯誤", "文件不可讀取。"); \
            break; \
        case FileRead::FileReadError::ContentError: \
            QMessageBox::critical(nullptr, "内容錯誤", "内容無效或文件損壞。"); \
            break; \
        case FileRead::FileReadError::UnknownError: \
            QMessageBox::critical(nullptr, "未知錯誤", "讀取文件時出現了錯誤。"); \
            break; \
    }\
    qApp->exit(static_cast<int>(code))

#define THROW_CRITICAL(msg) \
    QMessageBox::critical(nullptr, "錯誤", msg); \
    qApp->exit(1)

#endif
