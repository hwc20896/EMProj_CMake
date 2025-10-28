#pragma once

#include <format>
#include <iostream>

// Log macro
#define LOG(msg) std::cout << "[INFO]\t" << msg << "\n"
#define ERROR(msg) std::cout << "[ERROR]\t" << msg << "\n"
#define WARNING(msg) std::cout << "[WARNING]\t" << msg << "\n"

//  Throw critical
#define THROW_FILE_CRITICAL(code, msg) \
    ERROR(msg);\
    switch (code){\
        case FileRead::Error::FileNotFound: \
            QMessageBox::critical(nullptr, "無法找到文件", "所需文件不存在。"); \
            break; \
        case FileRead::Error::ReadError: \
            QMessageBox::critical(nullptr, "讀取錯誤", "文件不可讀取。"); \
            break; \
        case FileRead::Error::ContentError: \
            QMessageBox::critical(nullptr, "内容錯誤", "内容無效或文件損壞。"); \
            break; \
        case FileRead::Error::UnknownError: \
            QMessageBox::critical(nullptr, "未知錯誤", "讀取文件時出現了錯誤。"); \
            break; \
    }\
    qApp->exit(static_cast<int>(code))

#define THROW_CRITICAL(msg) \
    QMessageBox::critical(nullptr, "錯誤", msg); \
    qApp->exit(1)

#define SINGLETON(cls)\
    public:\
        static cls& instance(){\
            static cls insl;\
            return insl;\
        }\
        \
        cls(const cls&) = delete;\
        cls(cls&&) = delete;\
        cls& operator=(const cls&) = delete;\
        cls& operator=(cls&&) = delete;\
    private:\
        cls() = default;

#define SINGLETON_WITHOUT_CONSTRUCTOR(cls)\
    public:\
        static cls& instance(){\
            static cls insl;\
                return insl;\
            }\
        \
        cls(const cls&) = delete;\
        cls(cls&&) = delete;\
        cls& operator=(const cls&) = delete;\
        cls& operator=(cls&&) = delete;\
    private:\
        cls();

