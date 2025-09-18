#include "widget_containers/mainwidget.hpp"
#include <QApplication>

#include "utilities/defines.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QObject::connect(&app, &QApplication::aboutToQuit, [] {
        LOG("Application quitting.");
    });

    MainWidget widget;
    widget.setFixedSize(1000, 700);
    widget.show();
    return app.exec();
}