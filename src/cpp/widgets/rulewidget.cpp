#include "widgets/rulewidget.hpp"
#include "widgets/templatewidget.hpp"
#include "utilities/fileread.hpp"
#include "utilities/database.hpp"

#include "ui_rulewidget.h"

RuleWidget::RuleWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::RuleWidget) {
    ui_->setupUi(this);

    corrSound_ = new QSoundEffect(this);
    corrSound_->setSource({"qrc:/SoundEffects/sounds/bingo.wav"});
    corrSound_->setVolume(0.5f);

    incorrSound_ = new QSoundEffect(this);
    incorrSound_->setSource({"qrc:/SoundEffects/sounds/ohno.wav"});
    incorrSound_->setVolume(0.5f);

    connect(ui_->corrSoundPreview, &QPushButton::clicked, this, [this]{corrSound_->play();});
    connect(ui_->incorrSoundPreview, &QPushButton::clicked, this, [this]{incorrSound_->play();});

    connect(ui_->returnButton, &QPushButton::clicked, this, &RuleWidget::returnToIntro);

    //  Widget tags
    ui_->corrSoundPreview->setObjectName("navigator");
    ui_->incorrSoundPreview->setObjectName("navigator");
    ui_->returnButton->setObjectName("navigator");
    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/intro.css").value_or(""));
}

RuleWidget::~RuleWidget() {
    delete ui_;
}

void RuleWidget::setRuleText(const std::string& blockText, const int displayQuantity) const {
    const auto basisLawCount     = Data::database.getQuestionCount(1),
               constitutionCount = Data::database.getQuestionCount(2);

    ui_->ruleText->setText(
        QString::fromStdString(
            std::format(ruleText, blockText, displayQuantity, basisLawCount, constitutionCount)
        )
    );
}
