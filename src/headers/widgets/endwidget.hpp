#pragma once
#ifndef ENDWIDGET_HPP
#define ENDWIDGET_HPP
#include <QLabel>
#include <vector>
#include <tuple>

#include "elements/muteswitch.hpp"
#include "elements/gamemodechooser.hpp"

//  PIMPL pattern
namespace Ui {
    class EndWidget;
}

class EndWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit EndWidget(const std::tuple<int,int>& result, bool isMuted, int currentMode, int64_t totalTime, QWidget* parent = nullptr);
        ~EndWidget() override;
        [[nodiscard]] bool getMutedState() const;

        [[nodiscard]] int getCurrentMode() const;
    private:
        Ui::EndWidget* ui_;
        MuteSwitch* muteSwitch_;
        QLabel* background_;
        GamemodeChooser* chooser_;
    signals:
        void restart(bool isMuted);
        void toAppInfo();
};

#endif