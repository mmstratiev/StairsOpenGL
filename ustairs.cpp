#include "ustairs.h"
#include <QDebug>
UStairs::UStairs(float stepWidth, float stepHeight, float stepDepth, int segmentHeight,
                 float stairsHeight, float platformDepth) :
    PlatformStairs(stepWidth, stepHeight, stepDepth, segmentHeight, stairsHeight, platformDepth)
{

}

UStairs::UStairs(float stepWidth, float stepHeight, float stepDepth, int segmentHeight,
                 float stairsHeight, float platformDepth, QVector3D startPos) :
    PlatformStairs(stepWidth, stepHeight, stepDepth, segmentHeight, stairsHeight, platformDepth, startPos)
{

}

void UStairs::buildVertexes()
{
    this->vertexes.clear();

    int platformsPlaced = 0;
    int firstIndex = 0;
    int stepsPlaced = 0;
    int lastIndex = stairsHeight/stepHeight;
    bool temp = isPositiveZ;

    for(int i = firstIndex; i < lastIndex; i++){
        float x = startPos.x();
        float y = startPos.y()+stepHeight*i-stepHeight*platformsPlaced;
        float z = startPos.z()+stepDepth*stepsPlaced;

        StepType stepType = MiddleStep;
        if(i == firstIndex){
            stepType = FirstStep;
        }
        else if(i == lastIndex-1){
            stepType = LastStep;
        }
        else if(i % segmentHeight == 0){
            addPlatform(x+stepWidth, y-stepHeight, isPositiveZ ? z+platformDepth-stepDepth*2 : z);
            platformsPlaced++;
            lastIndex++;
            isPositiveZ = !isPositiveZ;
            stepsPlaced += isPositiveZ ? 1 : -1;
            continue;
        }
        addStep(isPositiveZ ? x+stepWidth : x, y, z, stepType);
        stepsPlaced += isPositiveZ ? 1 : -1;
    }
    this->setIsPositiveZ(temp);
}

void UStairs::addPlatform(float x, float y, float z)
{
    float temp = stepDepth;
    float temp2 = stepWidth;
    stepDepth = platformDepth-stepDepth;
    stepWidth *= 2;

    if(!isPositiveZ){
        addBack(x, y, z-stepDepth);
    }
    else{
        addFront(x,y,z);
    }
    addTop(x,y+stepHeight,z);
    addBottom(x, y, z, true);
    addLeft(x-stepWidth,y,z, true);
    addRight(x, y+stepHeight, z, true);

    stepDepth = temp;
    stepWidth = temp2;
}
