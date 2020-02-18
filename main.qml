import QtQuick.Scene3D 2.0
import QtQuick 2.2 as QQ2
import QtQuick.Window 2.13

import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Logic 2.0
import Qt3D.Extras 2.0
import Qt3D.Animation 2.9

Scene3D {
    id: scene3d
    anchors.fill: parent
    aspects: ["render", "logic", "input"]

    signal bbox(entity: Entity)

    Entity {
        id: root
        components: [
            RenderSettings {
                activeFrameGraph: ForwardRenderer {
                    id: renderer
                    camera: mainCamera
                }
            },
            InputSettings {}
        ]

        Camera {
            id: mainCamera
            projectionType: CameraLens.PerspectiveProjection
            fieldOfView: 45
            aspectRatio: 16/9
            nearPlane : 0.1
            farPlane : 1000.0
            position: Qt.vector3d(0.0, 0.0, -4.0)
            upVector: Qt.vector3d(0.0, 1.0, 0.0)
            viewCenter: Qt.vector3d(0.0, 0.5, 0.0)
        }

        SOrbitCameraController {
            camera: mainCamera
        }

        Entity {
            id: meshEntity
            components: [
                Mesh {
                    source: "qrc:/irb140.obj"
                    onStatusChanged: { if(status == Mesh.Ready) scene3d.bbox(meshEntity); }
                },
                PhongMaterial {
                    diffuse: "#ff9100"
                },
                Transform {
                    rotationX: -90
                    rotationY: 90
                }
            ]
        }

        Entity {
            id: coneEntity
            components: [
                ConeMesh {
                    topRadius: 0
                    bottomRadius: 0.3
                    length: 0.5
                    onGeometryChanged: { if(status == Mesh.Ready) scene3d.bbox(meshEntity); }
                },
                PhongMaterial {
                    diffuse: "#3090b0"
                },
                Transform {
                    translation: Qt.vector3d(1, 0, 0)
                }

            ]
        }

        Entity {
            components: [
                PointLight {
                    color: "white"
                    intensity: 0.9
                    constantAttenuation: 1.0
                    linearAttenuation: 0.0
                    quadraticAttenuation: 0.0025
                },
                Transform {
                    translation: Qt.vector3d(1.0, 3.0, -2.0)
                }
            ]
        }
    }
}
