#include <QApplication>

#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    QString format = "yyyy.MM.dd";
    QString str = "2025.02.17";
    auto date = QDateTime::fromString(str, format);;
    qDebug() << date;

    return app.exec();
}

