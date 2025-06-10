#include "introwidget.hpp"

IntroWidget::IntroWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::IntroWidget) {
    ui_->setupUi(this);
    isMuted = false;

    //  Connections
    connect(ui_->ruleButton, &QPushButton::clicked, this, &IntroWidget::toRulePage);
    connect(ui_->startButton, &QPushButton::clicked, this, &IntroWidget::start);
}

IntroWidget::~IntroWidget() {
    delete ui_;
}