#ifndef BOUNDINGBOXHELPER_H
#define BOUNDINGBOXHELPER_H

#include <QObject>
#include <Qt3DCore/QEntity>

class BoundingBoxHelper : public QObject
{
    Q_OBJECT
public:
    explicit BoundingBoxHelper(QObject *parent = nullptr);

signals:

public slots:
    void bbox(Qt3DCore::QEntity *entity);
};

#endif // BOUNDINGBOXHELPER_H
