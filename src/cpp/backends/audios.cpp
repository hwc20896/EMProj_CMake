#include "backends/audios.hpp"

EMProj_CMake_Backend::Audios::Audios() : player_(new QMediaPlayer()) {
    //  Background Music
    audioOutput_ = new QAudioOutput();
    player_->setAudioOutput(audioOutput_);
    player_->setSource({"qrc:/BGM/sounds/OMFG_Pizza.mp3"});
    audioOutput_->setVolume(0.15f);
    player_->setLoops(QMediaPlayer::Infinite);

    //  Sound Effects
    correctSound_ = new QSoundEffect();
    correctSound_->setSource({"qrc:/SoundEffects/sounds/bingo.wav"});

    incorrectSound_ = new QSoundEffect();
    incorrectSound_->setSource({"qrc:/SoundEffects/sounds/ohno.wav"});
}

EMProj_CMake_Backend::Audios::~Audios() {
    delete audioOutput_;
    delete player_;
    delete correctSound_;
    delete incorrectSound_;
}

void EMProj_CMake_Backend::Audios::setBackgroundMuted(const bool muted) {
    isBackgroundMuted_ = muted;
    audioOutput_->setMuted(isBackgroundMuted_);
}

bool EMProj_CMake_Backend::Audios::reverseBackgroundMuted() {
    isBackgroundMuted_ = !isBackgroundMuted_;
    audioOutput_->setMuted(isBackgroundMuted_);
    return isBackgroundMuted_;
}

bool EMProj_CMake_Backend::Audios::getBackgroundMuted() const {
    return isBackgroundMuted_;
}

void EMProj_CMake_Backend::Audios::playBackgroundMusic() const {
    if (player_->playbackState() != QMediaPlayer::PlayingState) {
        player_->play();
    }
}

void EMProj_CMake_Backend::Audios::stopBackgroundMusic() const {
    if (player_->playbackState() == QMediaPlayer::PlayingState) {
        player_->stop();
    }
}

void EMProj_CMake_Backend::Audios::setEffectMuted(const bool muted) {
    isEffectMuted_ = muted;
    correctSound_->setMuted(isEffectMuted_);
    incorrectSound_->setMuted(isEffectMuted_);
}

void EMProj_CMake_Backend::Audios::playCorrect() const {
    correctSound_->play();
}

void EMProj_CMake_Backend::Audios::playIncorrect() const {
    incorrectSound_->play();
}