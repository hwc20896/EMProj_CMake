#pragma once

#include <QAudioOutput>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <memory>
#include "utilities/defines.hpp"

namespace EMProj_CMake_Backend {
    class Audios final {
        SINGLETON_WITHOUT_CONSTRUCTOR(Audios)
        public:
            //  Background Music

            /**
             * @brief Set the background music muted state.
             *
             * @param muted True to mute, False to unmute.
             */
            void setBackgroundMuted(bool muted);

            /**
             * @brief Get the current background music muted state.
             *
             * @return True if muted, False otherwise.
             */
            [[nodiscard]]
            bool getBackgroundMuted() const;

            /**
             * @brief Reverse the current background music muted state.
             *
             * @return The new muted state after reversal.
             */
            bool reverseBackgroundMuted();

            /**
             * @brief Start the background music.
             */
            void playBackgroundMusic() const;

            /**
             * @brief Stop the background music.
             */
            void stopBackgroundMusic() const;

            //  Sound Effect

            /**
             * @brief Set the sound effects muted state.
             *
             * @param muted True to mute, False to unmute.
             */
            void setEffectMuted(bool muted);

            /**
             * @brief Play the correct answer sound effect.
             */
            void playCorrect() const;

            /**
             * @brief Play the incorrect answer sound effect.
             */
            void playIncorrect() const;
        private:
            //  Background Music
            std::unique_ptr<QAudioOutput> audioOutput_;
            std::unique_ptr<QMediaPlayer> player_;
            bool isBackgroundMuted_ = false;

            //  Sound Effects
            std::unique_ptr<QSoundEffect> correctSound_;
            std::unique_ptr<QSoundEffect> incorrectSound_;
            bool isEffectMuted_ = false;
    };
}
