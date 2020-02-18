#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>

#include "boundingboxhelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    BoundingBoxHelper bboxHelper;

    QQuickView view;
    view.resize(500, 500);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));

    auto root = view.rootObject();
    QObject::connect(root, SIGNAL(bbox(Qt3DCore::QEntity*)),
                        &bboxHelper, SLOT(bbox(Qt3DCore::QEntity*)));

    view.show();

    return app.exec();
}
