#pragma once

#include <QAudioOutput>
#include <QSoundEffect>
#include <QMediaPlayer>

namespace EMProj_CMake_Backend {
    class Audios final {
        public:
            Audios();
            ~Audios();

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
            QAudioOutput* audioOutput_;
            QMediaPlayer* player_;
            bool isBackgroundMuted_ = false;

            //  Sound Effects
            QSoundEffect* correctSound_, * incorrectSound_;
            bool isEffectMuted_ = false;
    };

    inline Audios audio_;
}
