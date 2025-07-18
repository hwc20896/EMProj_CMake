#pragma once
#ifndef OUTROWIDGET_HPP
#define OUTROWIDGET_HPP
#include <QStackedWidget>
#include "endwidget.hpp"
#include "appinfowidget.hpp"
#include <vector>

class OutroWidget final : public QStackedWidget {
    Q_OBJECT
    public:
        explicit OutroWidget(Result result, bool isMuted, const std::vector<int64_t>& timeStamps, QWidget* parent = nullptr);
        ~OutroWidget() override;
    private:
        EndWidget* endWidget_;
        AppInfoWidget* appInfoWidget_;
    signals:
        void replay(bool isMuted);
};

#endif