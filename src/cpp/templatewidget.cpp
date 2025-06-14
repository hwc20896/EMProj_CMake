#include "templatewidget.hpp"
#include <QFile>

QuestionWidget::QuestionWidget(QuestionData&& question, const int index, QWidget* parent) : QWidget(parent), question_(question) {
    //  TODO: ui
}

QuestionWidget::~QuestionWidget() {
    //  TODO: ui
}


QString QuestionWidget::getStyleFromURI(const QString& uri) {
    if (QFile file(uri); file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString result = file.readAll();
        file.close();
        return result;
    }
    return "";
}