#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.setWindowTitle("ProfileEdit 2.0");
	w.show();

	return a.exec();
}
