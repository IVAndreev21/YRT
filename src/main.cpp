#include "mainmenu.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    w.setWindowTitle("Main Menu");
    w.show();
    return a.exec();
}
