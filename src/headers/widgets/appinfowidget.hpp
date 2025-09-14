#pragma once
#ifndef APPINFOWIDGET_HPP
#define APPINFOWIDGET_HPP
#include <QWidget>

//  PIMPL pattern
namespace Ui {
    class AppInfoWidget;
}

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