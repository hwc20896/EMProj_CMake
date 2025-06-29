#pragma once
#ifndef RESULT_HPP
#define RESULT_HPP

struct Result {
    int correct = 0;
    int total = 0;

    [[nodiscard]]
    double getPercentage() const {
        return correct * 1.0 / total * 100;
    }
};

#endif