#include "introwidget.hpp"

#include <QPixmap>
#include <memory>

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

    //  Widget tags
    ui_->startButton->setObjectName("navigator");
    ui_->muteSwitch->setObjectName("icon");
    ui_->ruleButton->setObjectName("navigator");
    this->setObjectName("root");
    this->setStyleSheet(QuestionWidget::getStyleFromURI(":/CSS/src/css/intro.css"));

    label_ = new QLabel(this);
    label_->setPixmap({":/BackgroundImages/backgrounds/firstpagebg.png"});
    label_->setGeometry(0,0,1000,700);
    label_->lower();
}

IntroWidget::~IntroWidget() {
    delete ui_;
}
