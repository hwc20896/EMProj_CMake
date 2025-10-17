#include "elements/muteswitch.hpp"

#include "backends/audios.hpp"
using EMProj_CMake_Backend::Audios;

MuteSwitch::MuteSwitch(const QSize iconSize, const bool currentState, QWidget* parent) : QPushButton(parent), isMuted(currentState) {
    this->setIconSize(iconSize);
    this->setObjectName("icon");
    Audios::instance().setBackgroundMuted(currentState);

    muted_.addFile(":/Drawables/drawables/mute.png");
    unmuted_.addFile(":/Drawables/drawables/unmute.png");

    connect(this, clicked, [this] {
        isMuted = Audios::instance().reverseBackgroundMuted();
        this->setIcon(isMuted? muted_ : unmuted_);
    });
    this->setIcon(isMuted? muted_ : unmuted_);
}

bool MuteSwitch::getMutedState() const {
    return isMuted;
}

void MuteSwitch::setMutedState(const bool muted) {
    isMuted = muted;
    Audios::instance().setBackgroundMuted(muted);
    this->setIcon(isMuted? muted_ : unmuted_);
}
