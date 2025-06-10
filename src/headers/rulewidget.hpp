#pragma once
#ifndef RULEWIDGET_HPP
#define RULEWIDGET_HPP
#include "ui_rulewidget.h"
#include <QSoundEffect>

class RuleWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit RuleWidget(QWidget* parent = nullptr);
        ~RuleWidget() override;
    private:
        Ui::RuleWidget* ui_;
        QSoundEffect* corrSound_, * incorrSound_;
    signals:
        void returnToIntro();
};


#endif