#include "widget_containers/outrowidget.hpp"

OutroWidget::OutroWidget(const std::tuple<int, int>& result, const bool isMuted, const int currentMode,  const int64_t totalTime, QWidget* parent)
: QStackedWidget(parent), endWidget_(new EndWidget(result, isMuted, currentMode, totalTime)), appInfoWidget_(new AppInfoWidget){
    this->addWidget(endWidget_);
    this->addWidget(appInfoWidget_);
    this->setCurrentWidget(endWidget_);

    connect(endWidget_, &EndWidget::toAppInfo, this, [this] {
        this->setCurrentWidget(appInfoWidget_);
    });
    connect(appInfoWidget_, &AppInfoWidget::returnToEnd, this, [this] {
        this->setCurrentWidget(endWidget_);
    });
    connect(endWidget_, &EndWidget::restart, this, [this] {
        emit replay(endWidget_->getMutedState());
    });
}

OutroWidget::~OutroWidget() {
    delete endWidget_;
    delete appInfoWidget_;
}

int OutroWidget::getCurrentMode() const {
    return endWidget_->getCurrentMode();
}
