#include "platformstairs.h"
#include "qdebug.h"
PlatformStairs::PlatformStairs(float stepWidth, float stepHeight, float stepDepth, int segmentHeight,
                               float stairsHeight, float platformDepth) :
    Stairs(stepWidth, stepHeight, stepDepth, stairsHeight)
{
    this->setSegmentHeight(segmentHeight);
    this->setPlatformDepth(platformDepth);
}

PlatformStairs::PlatformStairs(float stepWidth, float stepHeight, float stepDepth,
                               int segmentHeight, float stairsHeight, float platformDepth, QVector3D startPos) :
    Stairs(stepWidth, stepHeight, stepDepth, stairsHeight, startPos)
{
    this->setSegmentHeight(segmentHeight);
    this->setPlatformDepth(platformDepth);
}

void PlatformStairs::buildVertexes()
{
    this->vertexes.clear();

    int platformsPlaced = 0;
    int depth = isPositiveZ ? 1 : -1;
    int firstIndex = 0;
    int lastIndex = stairsHeight/stepHeight;
    float x, y, z;

    for(int i = firstIndex; i < lastIndex; i++){

        x = startPos.x();//+stepWidth/2.0f;
        y = startPos.y()+stepHeight*i - stepHeight*platformsPlaced;
        z = startPos.z()+stepDepth*i*depth + (platformDepth-stepDepth*2)*platformsPlaced*depth;

        StepType stepType = MiddleStep;
        if(i == firstIndex){
            stepType = FirstStep;
        }
        else if(i == lastIndex-1){
            stepType = LastStep;
        }
        else if(i % segmentHeight == 0){
            addPlatform(x, y-stepHeight, isPositiveZ ? z+platformDepth-stepDepth*2 : z);
            platformsPlaced++;
            lastIndex++;
            continue;
        }
        addStep(x, y, z, stepType);
    }
}

void PlatformStairs::addPlatform(float x, float y, float z)
{
    //changes stepDepth, draws a platform with the new depth and resets to the old depth
    float temp = stepDepth;
    //platformDepth-stepDepth because platform starts at the begining of the last step, not at the end
    stepDepth = platformDepth-stepDepth;
    addTop(x,y+stepHeight,z);
    addBottom(x, y, z, true);
    addLeft(x-stepWidth,y,z, true);
    addRight(x, y+stepHeight, z, true);
    stepDepth = temp;
}
