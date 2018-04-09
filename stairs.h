#ifndef STAIRS_H
#define STAIRS_H
#include <vector>
#include <QVector3D>
#include "vertex.h"
#include "drawableglinterface.h"

class Stairs : public DrawableGLInterface
{
public:
    enum StepType{
        FirstStep,
        MiddleStep,
        LastStep
    };

    //Constructors
    Stairs(float stepWidth, float stepHeight, float stepDepth, float stairsHeight);
    Stairs(float stepWidth, float stepHeight, float stepDepth, float stairsHeight, QVector3D startPos);

    //Getters
    virtual const std::vector<Vertex> &getVertexes() const;
    virtual const Vertex* getVertexesArray() const;
    virtual int getStepsCount() const;

    //Setters
    void setStepWidth(double stepWidth);
    void setStepHeight(double stepHeight);
    void setStepDepth(double stepDepth);
    void setStairsHeight(double stairsHeight);
    void setStartPos(QVector3D startPos);
    void setIsPositiveZ(bool isPositiveZ);

    //Vertex manipulators
    virtual void buildVertexes();
    virtual void addStep(float x, float y, float z, StepType);
private:

protected:
    float stepWidth;
    float stepHeight;
    float stepDepth;
    float stairsHeight;
    bool isPositiveZ = false;
    QVector3D startPos;
    int stepsCount;
    std::vector<Vertex> vertexes;

    //adds a face facing +z
    virtual void addFront(float x, float y, float z);
    //adds a face facing -z
    virtual void addBack(float x, float y, float z);
    //+y
    virtual void addTop(float x, float y, float z);
    //-y
    virtual void addBottom(float x, float y, float z, bool isFirstStep);
    //-x
    virtual void addLeft(float x, float y, float z, bool isFirstLastStep);
    //+x
    virtual void addRight(float x, float y, float z, bool isFirstLastStep);
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

//Getters
inline const std::vector<Vertex> &Stairs::getVertexes() const { return this->vertexes; }
inline const Vertex *Stairs::getVertexesArray() const { return &this->vertexes[0]; }
inline int Stairs::getStepsCount() const { return this->stepsCount; }

//Setters
inline void Stairs::setStepWidth(double stepWidth) { this->stepWidth = stepWidth; }
inline void Stairs::setStepDepth(double stepDepth) { this->stepDepth = stepDepth; }
inline void Stairs::setStartPos(QVector3D startPos) { this->startPos = startPos; }
inline void Stairs::setIsPositiveZ(bool isPositiveZ) { this->isPositiveZ = isPositiveZ; }

inline void Stairs::setStepHeight(double stepHeight){
    this->stepHeight = stepHeight;
    this->stepsCount = this->stairsHeight/stepHeight;
}
inline void Stairs::setStairsHeight(double stairsHeight){
    this->stairsHeight = stairsHeight;
    this->stepsCount = stairsHeight/this->stepHeight;
}

#endif // STAIRS_H
