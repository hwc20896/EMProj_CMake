#include "elements/muteswitch.hpp"

MuteSwitch::MuteSwitch(const QSize iconSize, const bool currentState, QWidget* parent) : QPushButton(parent), isMuted(currentState) {
    this->setIconSize(iconSize);
    this->setObjectName("icon");

    muted_.addFile(":/Drawables/drawables/mute.png");
    unmuted_.addFile(":/Drawables/drawables/unmute.png");

    connect(this, clicked, [this] {
        isMuted = !isMuted;
        this->setIcon(isMuted? muted_ : unmuted_);
        emit mutedStateChanged(isMuted);
    });
    this->setIcon(isMuted? muted_ : unmuted_);
}

bool MuteSwitch::getMutedState() const {
    return isMuted;
}

void MuteSwitch::setMutedState(const bool muted) {
    isMuted = muted;
    this->setIcon(isMuted? muted_ : unmuted_);
}
