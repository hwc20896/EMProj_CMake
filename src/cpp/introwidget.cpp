#include "introwidget.hpp"

IntroWidget::IntroWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::IntroWidget) {
    ui_->setupUi(this);
    isMuted = false;

    muted.addFile(":/Drawables/drawables/mute.png");
    unmuted.addFile(":/Drawables/drawables/unmute.png");

    //  Connections
    connect(ui_->ruleButton, &QPushButton::clicked, this, &IntroWidget::toRulePage);
    connect(ui_->startButton, &QPushButton::clicked, this, &IntroWidget::start);
    connect(ui_->muteSwitch, &QPushButton::clicked, this, [this] {
        isMuted = !isMuted;
        ui_->muteSwitch->setIcon(isMuted? muted: unmuted);
    });
    ui_->muteSwitch->setIcon(unmuted);
}

IntroWidget::~IntroWidget() {
    delete ui_;
}