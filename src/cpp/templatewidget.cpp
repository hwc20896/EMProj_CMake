#include "templatewidget.hpp"
#include <QFile>
#include <ranges>
#include <array>

QuestionWidget::QuestionWidget(QuestionData&& question, const int index, QWidget* parent)
: QWidget(parent), ui_(new Ui::TemplateWidget), question_(question) {
    ui_->setupUi(this);

    correctText = question_.options_[question_.correctOption_];
    std::ranges::shuffle(question_.options_, RANDOM_ALGORITHM);

    const std::array optionButtons = {ui_->optionA, ui_->optionB, ui_->optionC, ui_->optionD};
    for (const auto button : optionButtons) button->hide();
    for (const auto& [text, button] : std::views::zip(question_.options_, optionButtons)) {
        button->setText(text);
        button->setVisible(true);
    }
}

QuestionWidget::~QuestionWidget() {
    delete ui_;
}

QString QuestionWidget::getStyleFromURI(const QString& uri) {
    if (QFile file(uri); file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString result = file.readAll();
        file.close();
        return result;
    }
    return "";
}