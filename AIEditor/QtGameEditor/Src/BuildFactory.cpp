#include "BuildFactory.h"
#include "BezierCurveItem.h"

BezierCurveItem* BuildFactory::buildBezierCurveItem()
{
	return new BezierCurveItem();
}