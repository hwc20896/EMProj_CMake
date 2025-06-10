#pragma once
#ifndef RULEWIDGET_HPP
#define RULEWIDGET_HPP
#include <QWidget>

#ifdef SOUND_IN_RULE
#include <QSoundEffect>
#endif

class RuleWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit RuleWidget(QWidget* parent = nullptr);
        ~RuleWidget() override;
};


#endif