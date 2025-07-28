#include "mainwidget.hpp"
#include <QApplication>
#include <QSqlDatabase>

#include "utilities/defines.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    //  Database initialization
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.db");
    if (database.open()) {
        LOG("Starting application");
        MainWidget widget(database);
        widget.setFixedSize(1000,700);
        widget.show();
        return app.exec();
    }
    ERROR("Unable to open database");
    return 3;
}