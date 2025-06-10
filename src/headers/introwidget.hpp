#pragma once
#ifndef INTROWIDGET_H
#define INTROWIDGET_H
#include "ui_introwidget.h"
#include <QIcon>

class IntroWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit IntroWidget(QWidget* parent = nullptr);
        ~IntroWidget() override;
    private:
        Ui::IntroWidget* ui_;
        QIcon muted, unmuted;
        bool isMuted;
    signals:
        void toRulePage();
        void start();
};

#endif