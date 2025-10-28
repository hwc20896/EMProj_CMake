#include "widgets/rulewidget.hpp"
#include "widgets/templatewidget.hpp"
#include "utilities/fileread.hpp"
#include "backends/database.hpp"
#include <tuple>

#include "ui_rulewidget.h"

using EMProj_CMake_Backend::Database;

#ifndef NO_SOUND_EFFECT_PREVIEW
#include "backends/audios.hpp"
using EMProj_CMake_Backend::Audios;
#endif

RuleWidget::RuleWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::RuleWidget) {
    ui_->setupUi(this);

#ifndef NO_SOUND_EFFECT_PREVIEW
    connect(ui_->corrSoundPreview, &QPushButton::clicked, this, [this]{Audios::instance().playCorrect();});
    connect(ui_->incorrSoundPreview, &QPushButton::clicked, this, [this]{Audios::instance().playIncorrect();});
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

    backgroundImage = new QLabel(this);
    backgroundImage->setPixmap({":/BackgroundImages/backgrounds/qnabg.png"});
    backgroundImage->setGeometry(0,0,1000,700);
    backgroundImage->lower();

    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/intro.css").value_or(""));
}

RuleWidget::~RuleWidget() {
    delete ui_;
}

void RuleWidget::setRuleText(const std::string& blockText, const int displayQuantity) const {
    const auto data = Database::instance().getQuestionCount();
    const auto [constitutionCount, basisLawCount] = std::make_tuple(data[0], data[1]);

    ui_->ruleText->setText(
        QString::fromStdString(
            std::format(ruleText, blockText, displayQuantity, basisLawCount, constitutionCount)
        )
    );
}
