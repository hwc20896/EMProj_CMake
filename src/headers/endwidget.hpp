#pragma once
#ifndef ENDWIDGET_HPP
#define ENDWIDGET_HPP
#include <vector>

#include "result.hpp"
#include "ui_endwidget.h"
#include "elements/muteswitch.hpp"
#include "elements/gamemodechooser.hpp"

class EndWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit EndWidget(const Result& result, bool isMuted, const std::vector<int64_t>& timeStamps, QWidget* parent = nullptr);
        ~EndWidget() override;
        [[nodiscard]] bool getMutedState() const;

        /**
         * @brief Converts the time to time format (mm:ss).
         * @param time Duration to be formatted.
         * @return Formatted duration.
         */
        static QString timeDisplay(int64_t time);

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