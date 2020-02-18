#include "boundingboxhelper.h"

#include <Qt3DRender>

BoundingBoxHelper::BoundingBoxHelper(QObject *parent)
    : QObject(parent)
{
}

void BoundingBoxHelper::bbox(Qt3DCore::QEntity *entity)
{
    qDebug() << "Called BoundingBoxHelper::bbox on" << entity;

    for(const auto &comp : entity->componentsOfType<Qt3DRender::QMesh>())
    {
        auto mesh = dynamic_cast<Qt3DRender::QMesh*>(comp);
        auto geom = mesh->geometry();
        auto attrs = geom->attributes();
        for(const auto &attr : attrs)
        {
            if(attr->name() != "vertexPosition") continue;
            int n = attr->count();
            auto buf = attr->buffer();
            const QByteArray &data = buf->data();
            float vmin[3], vmax[3];
            for(int i = 0; i < n; i++)
            {
                int vertexOffset = i * attr->byteStride();
                int offset = vertexOffset + attr->byteOffset();
                const char *rawData = &(data.constData()[offset]);
                auto value = reinterpret_cast<const float*>(rawData);
                for(int j = 0; j < 3; j++)
                {
                    vmin[j] = qMin(vmin[j], value[j]);
                    vmax[j] = qMax(vmax[j], value[j]);
                }
            }
            qDebug() << "Bounding box of mesh" << mesh << "is" << vmin[0] << vmin[1] << vmin[2] << vmax[0] << vmax[1] << vmax[2];
        }
    }
}
