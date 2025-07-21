#include "introwidget.hpp"

#include <QPixmap>
#include "utilities/fileread.hpp"

IntroWidget::IntroWidget(const bool defaultMuted, QWidget* parent) : QWidget(parent), ui_(new Ui::IntroWidget) {
    ui_->setupUi(this);

    //  Mute switch
    muteSwitch_ = new MuteSwitch({50,50}, defaultMuted, this);
    muteSwitch_->setGeometry(580,20,60,60);

    //  Connections
    connect(ui_->ruleButton, &QPushButton::clicked, this, &IntroWidget::toRulePage);
    connect(ui_->startButton, &QPushButton::clicked, this, &IntroWidget::start);

    //  Widget tags
    ui_->startButton->setObjectName("navigator");
    ui_->ruleButton->setObjectName("navigator");
    this->setObjectName("root");


    label_ = new QLabel(this);
    label_->setPixmap({":/BackgroundImages/backgrounds/firstpagebg.png"});
    label_->setGeometry(0,0,1000,700);
    label_->lower();
}

IntroWidget::~IntroWidget() {
    delete ui_;
    delete muteSwitch_;
}

void IntroWidget::blockStart() const {
    ui_->startButton->setDisabled(true);
    ui_->startButton->setToolTip("由於配置文件缺失，無法開始游戲。請到下載處Issue頁回報此問題。");
}

bool IntroWidget::getMutedState() const {
    return muteSwitch_->getMutedState();
}