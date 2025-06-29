#pragma once
#ifndef APPINFOWIDGET_HPP
#define APPINFOWIDGET_HPP
#include "ui_appinfowidget.h"

class AppInfoWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit AppInfoWidget(QWidget* parent = nullptr);
        ~AppInfoWidget() override;
    private:
        Ui::AppInfoWidget* ui_;
    signals:
        void returnToEnd();
};

#endif