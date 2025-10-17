#include "backends/questionbackend.hpp"
#include "backends/database.hpp"
#include "backends/audios.hpp"
#include <numeric>
#include <QEventLoop>
#include <QTimer>
using namespace std::chrono;
using EMProj_CMake_Backend::Audios, EMProj_CMake_Backend::Database;

//  class TimeCounter
void EMProj_CMake_Backend::TimeCounter::resetAll() {
    timestamps_.clear();
    endTime_ = {};
}

void EMProj_CMake_Backend::TimeCounter::start() {
    startTime_ = high_resolution_clock::now();
}

void EMProj_CMake_Backend::TimeCounter::stop() {
    endTime_ = high_resolution_clock::now();
    const auto duration = duration_cast<milliseconds>(endTime_ - startTime_).count();
    timestamps_.push_back(duration);
}

int64_t EMProj_CMake_Backend::TimeCounter::getTotalTime(){
    const auto totalTime = std::accumulate(timestamps_.begin(), timestamps_.end(), 0LL);
    resetAll();
    return totalTime;
}

//  class Scorer
void EMProj_CMake_Backend::Scorer::loadQuestion(const int gamemode, const int quantity) {
    questionPool_.clear();
    correctCount_ = 0;
    incorrectCount_ = 0;
    totalCount_ = quantity;

    questionPool_ = Database::instance().getQuestions(gamemode, quantity);
}

const QuestionData& EMProj_CMake_Backend::Scorer::operator[](const int index) const {
    if (index < 0 || index >= questionPool_.size()) {
        throw std::out_of_range("Index out of range in QuestionBackend::operator[]");
    }
    return questionPool_[index];
}

bool EMProj_CMake_Backend::Scorer::checkQuestion(const QString& answer, const int index) {
    if (index < 0 || index >= static_cast<int>(questionPool_.size())) {
        throw std::out_of_range("Index out of range in QuestionBackend::checkQuestion");
    }

    counter_.stop();

    cooldown(800);
    const auto& question = questionPool_[index];
    const bool isCorrect = answer == question.options_[question.correctOption_];

    if (isCorrect) {
        correctCount_++;
        Audios::instance().playCorrect();

    } else {
        incorrectCount_++;
        Audios::instance().playIncorrect();
    }

    return isCorrect;
}

std::tuple<int, int> EMProj_CMake_Backend::Scorer::getScore() const {
    return {correctCount_, incorrectCount_};
}

void EMProj_CMake_Backend::Scorer::startTimer() {
    counter_.start();
}

int64_t EMProj_CMake_Backend::Scorer::getTotalTime() {
    return counter_.getTotalTime();
}

int EMProj_CMake_Backend::Scorer::getAnsweredCount() const {
    return correctCount_ + incorrectCount_;
}

void EMProj_CMake_Backend::Scorer::cooldown(const int msec) {
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, &QEventLoop::quit);
    loop.exec();
}