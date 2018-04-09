#ifndef USTAIRS_H
#define USTAIRS_H
#include <vector>
#include "vertex.h"
#include "stairs.h"
#include "platformstairs.h"
class UStairs : public PlatformStairs
{
public:
    UStairs(float stepWidth, float stepHeight, float stepDepth, int segmentHeight,
            float stairsHeight, float platformDepth);
    UStairs(float stepWidth, float stepHeight, float stepDepth, int segmentHeight,
            float stairsHeight, float platformDepth, QVector3D startPos);

    virtual void buildVertexes();
protected:
    virtual void addPlatform(float x, float y, float z);
};

#endif // USTAIRS_H
