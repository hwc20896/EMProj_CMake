#pragma once
#ifndef INTROWIDGET_H
#define INTROWIDGET_H
#include "widget_containers/managementwidget.hpp"
#include <QLabel>

#include "elements/gamemodechooser.hpp"
#include "elements/muteswitch.hpp"

//  PIMPL pattern
namespace Ui {
    class IntroWidget;
}

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
        void setMutedState(bool muted);

        [[nodiscard]] int getCurrentMode() const;
    private:
        Ui::IntroWidget* ui_;
        MuteSwitch* muteSwitch_;

        QLabel* label_;

        GamemodeChooser* chooser_;
    signals:
        void toRulePage();
        void start();
};

#endif