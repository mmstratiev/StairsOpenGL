#include "stairs.h"
#include <QDebug>
#include <QVector3D>

//Constructors
Stairs::Stairs(float stepWidth, float stepHeight, float stepDepth, float stairsHeight)
{
    setStepWidth(stepWidth);
    setStepHeight(stepHeight);
    setStepDepth(stepDepth);
    setStairsHeight(stairsHeight);
    setStartPos(QVector3D(0.0f, 0.0f, 0.0f));
}

Stairs::Stairs(float stepWidth, float stepHeight, float stepDepth, float stairsHeight, QVector3D startPos)
{
    setStepWidth(stepWidth);
    setStepHeight(stepHeight);
    setStepDepth(stepDepth);
    setStairsHeight(stairsHeight);
    setStartPos(startPos);
}

void Stairs::buildVertexes()
{
    this->vertexes.clear();

    int firstIndex = 0;
    int lastIndex = stepsCount;
    float depth = isPositiveZ ? stepDepth : - stepDepth;
    float x,y,z;

    for(int i = firstIndex; i < lastIndex; i++){
        x = startPos.x();
        y = startPos.y()+stepHeight*i;
        z = startPos.z()+depth*i;

        StepType stepType;
        if(i == firstIndex){
            stepType = FirstStep;
        }
        else if(i == lastIndex-1){
            stepType = LastStep;
        }
        else{
            stepType = MiddleStep;
        }
        addStep(x, y, z, stepType);
    }
}

void Stairs::addStep(float x, float y, float z, StepType stepType)
{
    if(!isPositiveZ){
        addFront(x,y,z);
    }
    else{
        addBack(x, y, z-stepDepth);
    }

    if(stepType == LastStep){
        if(!isPositiveZ){
            addBack(x,y,z-stepDepth);
        }
        else{
            addFront(x, y, z);
        }
    }
    addTop(x,y+stepHeight,z);

    bool isFirst = stepType == FirstStep;

    addBottom(x, y, z, isFirst);
    addLeft(x-stepWidth,y,z, isFirst);
    addRight(x, y+stepHeight, z, isFirst);
}

void Stairs::addFront(float x, float y, float z)
{
    QVector3D color = Vertex::Color::Grey();
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y-=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x+=stepWidth, y+=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y, z), color));
}

void Stairs::addBack(float x, float y, float z)
{
    QVector3D color = Vertex::Color::Grey();
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y+=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x+=stepWidth, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x+=stepWidth, y-=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y, z), color));
}

void Stairs::addTop(float x, float y, float z)
{
    QVector3D color = Vertex::Color::LightGrey();
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z-=stepDepth), color));
    vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z+=stepDepth), color));
    vertexes.push_back(Vertex(QVector3D(x+=stepWidth, y, z), color));
}

void Stairs::addBottom(float x, float y, float z, bool isFirstStep)
{
    QVector3D color = Vertex::Color::DarkGrey();
    if(!isPositiveZ){
        vertexes.push_back(Vertex(QVector3D(x, y = isFirstStep ? y : y-=stepHeight, z), color));
        vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x, y = isFirstStep ? y : y+=stepHeight, z-=stepDepth), color));
        vertexes.push_back(Vertex(QVector3D(x, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x+=stepWidth, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x, y = isFirstStep ? y : y-=stepHeight, z+=stepDepth), color));
    }
    else{
        vertexes.push_back(Vertex(QVector3D(x, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x-=stepWidth, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x, y = isFirstStep ? y : y-=stepHeight, z-=stepDepth), color));
        vertexes.push_back(Vertex(QVector3D(x, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x+=stepWidth, y, z), color));
        vertexes.push_back(Vertex(QVector3D(x, y = isFirstStep ? y : y+=stepHeight, z+=stepDepth), color));
    }

}

void Stairs::addLeft(float x, float y, float z, bool isFirstLastStep)
{
    QVector3D color = Vertex::Color::Grey();
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z-=stepDepth),color));
    vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z+=stepDepth), color));
    vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z-=stepDepth), color));
    vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z), color));

    if(!isFirstLastStep){
        vertexes.push_back(Vertex(QVector3D(x, y, z), color));
        if(!isPositiveZ){
            vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z+=stepDepth), color));
            vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z), color));
        }
        else{
            vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z), color));
            vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z+=stepDepth), color));
        }
    }
}

void Stairs::addRight(float x, float y, float z, bool isFirstLastStep)
{
    QVector3D color = Vertex::Color::LightGrey();
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z-=stepDepth), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z), color));
    vertexes.push_back(Vertex(QVector3D(x, y, z+=stepDepth), color));

    if(!isFirstLastStep){
        vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z), color));
        if(!isPositiveZ){
            vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z), color));
            vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z-=stepDepth), color));
        }
        else{
            vertexes.push_back(Vertex(QVector3D(x, y-=stepHeight, z-=stepDepth), color));
            vertexes.push_back(Vertex(QVector3D(x, y+=stepHeight, z), color));
        }
    }
}
