#include "mainwidget.hpp"
#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    //  Database initialization
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.db");
    if (database.open()) {
        MainWidget widget(database);
        widget.setFixedSize(1000,700);
        widget.show();
        return app.exec();
    }
    return 3;
}