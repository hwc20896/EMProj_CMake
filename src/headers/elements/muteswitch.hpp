#pragma once
#ifndef MUTESWITCH_HPP
#define MUTESWITCH_HPP
#include <QPushButton>
#include <QIcon>

class MuteSwitch final : public QPushButton {
    Q_OBJECT
    public:
        explicit MuteSwitch(QSize iconSize, bool currentState, QWidget* parent = nullptr);
        [[nodiscard]] bool getMutedState() const;
        void setMutedState(bool muted);
    private:
        QIcon muted_, unmuted_;
        bool isMuted;
};

#endif
