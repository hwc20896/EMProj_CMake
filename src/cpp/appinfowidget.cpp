#include "appinfowidget.hpp"
#include "templatewidget.hpp"

AppInfoWidget::AppInfoWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::AppInfoWidget) {
    ui_->setupUi(this);

    connect(ui_->returnButton, &QPushButton::clicked, this, &AppInfoWidget::returnToEnd);

    ui_->returnButton->setObjectName("navigator");
    this->setStyleSheet(QuestionWidget::getStyleFromURI(":/CSS/src/css/outro.css"));
}

AppInfoWidget::~AppInfoWidget() {
    delete ui_;
}