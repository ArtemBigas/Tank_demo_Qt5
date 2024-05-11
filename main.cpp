
#include "shooter.h"
int main(int argc, char *argv[])
{
    QApplication tank(argc, argv);

    shooter window;

    window.setWindowTitle("Shooter");
    window.show();

    return tank.exec();
}
