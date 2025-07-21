#pragma once
#ifndef INTROWIDGET_H
#define INTROWIDGET_H
#include "managementwidget.hpp"
#include "elements/muteswitch.hpp"
#include "ui_introwidget.h"

class IntroWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit IntroWidget(bool defaultMuted, QWidget* parent = nullptr);
        ~IntroWidget() override;

        /**
         * @brief Disables the start button, preventing the game from starting.
         */
        void blockStart() const;
        [[nodiscard]] bool getMutedState() const;
        void setMutedState(const bool muted);
    private:
        Ui::IntroWidget* ui_;
        MuteSwitch* muteSwitch_;

        QLabel* label_;

    signals:
        void toRulePage();
        void start();
};

#endif