#ifndef __BUILDFACTORY_H
#define __BUILDFACTORY_H

class QGraphicsObject;
class BezierCurveItem;

class BuildFactory
{
public:
	BezierCurveItem* buildBezierCurveItem();
};

#endif // __BUILDFACTORY_H