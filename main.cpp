#include <QApplication>
#include "mainwindow.h"
#include <windows.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    HINSTANCE hd = qWinAppInst();
    std::vector<char> executablePath(MAX_PATH);
    DWORD result = ::GetModuleFileNameA((HMODULE)hd, &executablePath[0], static_cast<DWORD>(executablePath.size()));
    std::cout << std::string(executablePath.begin(), executablePath.begin() + result) << std::endl;

    return a.exec();
}
