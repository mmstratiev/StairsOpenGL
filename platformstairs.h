#ifndef PLATFORMSTAIRS_H
#define PLATFORMSTAIRS_H
#include "stairs.h"

class PlatformStairs : public Stairs
{
public:
    PlatformStairs(float stepWidth, float stepHeight, float stepDepth,
                   int segmentHeight, float stairsHeight, float platformDepth);
    PlatformStairs(float stepWidth, float stepHeight, float stepDepth,
                   int segmentHeight, float stairsHeight, float platformDepth, QVector3D startPos);

    virtual void buildVertexes();

    //Setters
    virtual void setPlatformDepth(float platformDepth);
    virtual void setSegmentHeight(int segmentHeight);
protected:
    float platformDepth;
    int segmentHeight;
    virtual void addPlatform(float x, float y, float z);
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

inline void PlatformStairs::setPlatformDepth(float platformDepth) { this->platformDepth = platformDepth; }

inline void PlatformStairs::setSegmentHeight(int segmentHeight){
    this->segmentHeight = segmentHeight;
    this->stepsCount = segmentHeight/this->stepHeight;
}


#endif // PLATFORMSTAIRS_H
