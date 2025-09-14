#include "widgets/appinfowidget.hpp"
#include "widgets/templatewidget.hpp"
#include "utilities/fileread.hpp"

#include "ui_appinfowidget.h"

AppInfoWidget::AppInfoWidget(QWidget* parent) : QWidget(parent), ui_(new Ui::AppInfoWidget) {
    ui_->setupUi(this);

    connect(ui_->returnButton, &QPushButton::clicked, this, &AppInfoWidget::returnToEnd);

    ui_->returnButton->setObjectName("navigator");
    this->setStyleSheet(FileRead::getStyleFromURI(":/CSS/src/css/outro.css").value_or(""));
}

AppInfoWidget::~AppInfoWidget() {
    delete ui_;
}