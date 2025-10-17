#include "widgets/rulewidget.hpp"
#include "widgets/templatewidget.hpp"
#include "utilities/fileread.hpp"
#include "backends/database.hpp"
#include <tuple>

#include "ui_rulewidget.h"

using EMProj_CMake_Backend::database;

#ifndef NO_SOUND_EFFECT_PREVIEW
#include "backends/audios.hpp"
using EMProj_CMake_Backend::audio_;
#endif

RuleWidget::RuleWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::RuleWidget) {
    ui_->setupUi(this);

#ifndef NO_SOUND_EFFECT_PREVIEW
    connect(ui_->corrSoundPreview, &QPushButton::clicked, this, [this]{audio_.playCorrect();});
    connect(ui_->incorrSoundPreview, &QPushButton::clicked, this, [this]{audio_.playIncorrect();});
#else
    ui_->corrSoundPreview->hide();
    ui_->incorrSoundPreview->hide();
    ui_->soundPreview->hide();
    ui_->line->hide();
#endif

    connect(ui_->returnButton, &QPushButton::clicked, this, &RuleWidget::returnToIntro);

    //  Widget tags
#ifndef NO_SOUND_EFFECT_PREVIEW
    ui_->corrSoundPreview->setObjectName("navigator");
    ui_->incorrSoundPreview->setObjectName("navigator");
#endif
    ui_->returnButton->setObjectName("navigator");
    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/intro.css").value_or(""));
}

RuleWidget::~RuleWidget() {
    delete ui_;
}

void RuleWidget::setRuleText(const std::string& blockText, const int displayQuantity) const {
    const auto basisLawCount     = database.getQuestionCount(1),
               constitutionCount = database.getQuestionCount(2);
    const auto data = database.getQuestionCount();

    ui_->ruleText->setText(
        QString::fromStdString(
            std::format(ruleText, blockText, displayQuantity, basisLawCount, constitutionCount)
        )
    );
}
