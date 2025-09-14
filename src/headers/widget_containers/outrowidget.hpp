#pragma once
#ifndef OUTROWIDGET_HPP
#define OUTROWIDGET_HPP
#include <QStackedWidget>
#include "widgets/endwidget.hpp"
#include "widgets/appinfowidget.hpp"
#include <vector>

class OutroWidget final : public QStackedWidget {
    Q_OBJECT
    public:
        explicit OutroWidget(Result result, bool isMuted, int currentMode, const std::vector<int64_t>& timeStamps, QWidget* parent = nullptr);
        ~OutroWidget() override;

        [[nodiscard]] int getCurrentMode() const;
    private:
        EndWidget* endWidget_;
        AppInfoWidget* appInfoWidget_;
    signals:
        void replay(bool isMuted);
};

#endif