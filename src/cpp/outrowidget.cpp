#include "outrowidget.hpp"

OutroWidget::OutroWidget(const Result result, const bool isMuted, const std::vector<int64_t>& timeStamps, QWidget* parent)
: QStackedWidget(parent), endWidget_(new EndWidget(result, isMuted, timeStamps)), appInfoWidget_(new AppInfoWidget){
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
