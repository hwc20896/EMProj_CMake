#include "widgets/endwidget.hpp"
#include "widgets/templatewidget.hpp"
#include "utilities/fileread.hpp"

#include <numeric>
#include "ui_endwidget.h"

#define NUM(num) QString::number(num)

EndWidget::EndWidget(const std::tuple<int, int>& result, const bool isMuted, const int currentMode, const int64_t totalTime, QWidget* parent)
: QWidget(parent), ui_(new Ui::EndWidget) {
    ui_->setupUi(this);
    muteSwitch_ = new MuteSwitch({50,50}, isMuted, this);
    muteSwitch_->setGeometry(410,20,60,60);

    const auto [correct, incorrect] = result;
    const auto percentage = static_cast<double>(correct)/(correct + incorrect) * 100;
    ui_->result->setText(QString("結果：%1 / %2: %3%").arg(NUM(correct), NUM(correct + incorrect), NUM(percentage)));
    QString imageUrl;

    /*  80% ~ 100% -> S
     *  55% ~ 80% -> A
     *  30% ~ 55% -> B
     *  0% ~ 30% -> C
     */
    if (percentage > 100 || percentage < 0) throw std::invalid_argument("Bruh u ever see a game with correct percentage over 100% or below 0%?");
    if (percentage > 80) imageUrl = ":/Tier/drawables/SRank.png";
    else if (percentage > 55) imageUrl = ":/Tier/drawables/ARank.png";
    else if (percentage > 30) imageUrl = ":/Tier/drawables/BRank.png";
    else imageUrl = ":/Tier/drawables/CRank.png";

    ui_->rankPic->setPixmap({imageUrl});

    //  Time
    using namespace std::chrono;
    ui_->timeDisplay->setText(QString("總答題時間：%1").arg(
        std::format("{:%M:%S}", duration_cast<seconds>(milliseconds(totalTime)))
    ));

    background_ = new QLabel(this);
    background_->setGeometry(0,0,1000,700);
    background_->setPixmap({":/BackgroundImages/backgrounds/outrobg.png"});
    background_->lower();

    connect(ui_->toAppInfo, &QPushButton::clicked, this, &EndWidget::toAppInfo);
    connect(ui_->replay, &QPushButton::clicked, this, [this]{emit restart(muteSwitch_->getMutedState());});
    connect(ui_->quitButton, &QPushButton::clicked, this, &QApplication::quit);

    //  Styles
    ui_->quitButton->setObjectName("navigator");
    ui_->replay->setObjectName("navigator");
    ui_->timeDisplay->setObjectName("result");
    ui_->result->setObjectName("result");
    ui_->toAppInfo->setObjectName("navigator");

    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/outro.css").value_or(""));

    //  Chooser
    chooser_ = new GamemodeChooser(currentMode, this);
    chooser_->setGeometry(290, 580, 200, 80);
}

EndWidget::~EndWidget() {
    delete ui_;
    delete muteSwitch_;
}

bool EndWidget::getMutedState() const {
    return muteSwitch_->getMutedState();
}

int EndWidget::getCurrentMode() const {
    return chooser_->getCurrentMode();
}