#ifndef DRAWABLEGLINTERFACE_H
#define DRAWABLEGLINTERFACE_H
#include "vertex.h"
#include "vector"
#include <QVector3D>
class DrawableGLInterface
{
public:
    virtual const std::vector<Vertex> &getVertexes() const = 0;
    virtual const Vertex *getVertexesArray() const = 0;
    virtual void buildVertexes() = 0;
};

#endif // DRAWABLEGLINTERFACE_H
