#pragma once

#include <chrono>
#include <vector>
#include <tuple>

#include "utilities/questiondata.hpp"
#include "utilities/defines.hpp"

namespace EMProj_CMake_Backend {
    class TimeCounter final {
        public:
            TimeCounter() = default;
            ~TimeCounter() = default;

            /** Starts the timer.*/
            void start();

            void stop();

            /** Gets the total recorded time in milliseconds.
             *
             * This function calculates the total time recorded across all intervals by summing up the
             * individual timestamps stored in the internal vector. It returns the total time in milliseconds.
             * After calling this function, the internal timestamps are reset to allow for new timing sessions.
             *
             * @return Total recorded time in milliseconds.
             */
            [[nodiscard]]
            int64_t getTotalTime();
        private:
            /** Resets all recorded timestamps.
             *
             * This function clears the internal vector that stores the timestamps of recorded intervals.
             * It is useful for starting a new timing session without any previous data.
             */
            void resetAll();
            std::vector<int64_t> timestamps_ = {};
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime_{}, endTime_{};
    };

    class Scorer final {
        SINGLETON(Scorer)
        public:
            void loadQuestion(int gamemode, int quantity);

            [[nodiscard]]
            const QuestionData& operator[](int index) const;

            void startTimer();

            [[nodiscard]]
            bool checkQuestion(const QString& answer, int index);

            [[nodiscard]]
            std::tuple<int, int> getScore() const;

            [[nodiscard]]
            int getAnsweredCount() const;

            [[nodiscard]]
            int64_t getTotalTime();

            /**
             *   @brief Suspend (msec) milliseconds, on another thread.
             *   @param msec Milliseconds you want to suspend.
             */
            static void cooldown(int msec);
        private:
            std::vector<QuestionData> questionPool_ = {};

            int correctCount_ = 0;
            int incorrectCount_ = 0;
            int totalCount_ = 0;

            TimeCounter counter_{};
    };
}