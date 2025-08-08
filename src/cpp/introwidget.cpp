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
    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/intro.css").value_or(""));

    label_ = new QLabel(this);
    label_->setPixmap({":/BackgroundImages/backgrounds/firstpagebg.png"});
    label_->setGeometry(0,0,1000,700);
    label_->lower();

    chooser_ = new GamemodeChooser(0, this);
    chooser_->setGeometry(440, 380, 180, 120);
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

void IntroWidget::setMutedState(const bool muted) {
    muteSwitch_->setMutedState(muted);
}