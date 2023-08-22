#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDesktopWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QPushButton button("Hello, Qt!");

    // Set the size of the button (which will be your main window).
    button.resize(400, 300); // For instance, 400x300

    // Center the window on the screen.
    QDesktopWidget desktop;
    int screenWidth = desktop.screen()->width();
    int screenHeight = desktop.screen()->height();
    int width = button.width();
    int height = button.height();
    button.setGeometry((screenWidth - width) / 2, (screenHeight - height) / 2, width, height);

    button.show();

    return app.exec();
}
