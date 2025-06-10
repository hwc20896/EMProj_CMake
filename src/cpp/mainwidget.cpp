#include "mainwidget.hpp"

MainWidget::MainWidget(const QSqlDatabase& database, QWidget* parent) :
    QStackedWidget(parent), database_(database), intro_(new IntroWidget)
{
    this->addWidget(intro_);

    this->setCurrentIndex(0);

    connect(intro_, &IntroWidget::toRulePage, this, [this] {
        this->setCurrentIndex(1);
    });
    connect(intro_, &IntroWidget::start, this, [this] {
        //  ...
    });
}

MainWidget::~MainWidget() {
    delete intro_;
}