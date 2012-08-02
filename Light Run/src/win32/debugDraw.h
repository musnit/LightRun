#include "cocos2d.h" 
using namespace cocos2d;

typedef struct
{
    CCPoint pt1;
    CCPoint pt2;
    float r;
    float g;
    float b;
} DebugLine;

typedef struct
{
    CCPoint pt;
    float r;
    float g;
    float b;
} DebugPoint;

class DebugDraw : public CCNode
{
public:
    static DebugDraw* create();

    DebugDraw();
    ~DebugDraw();
    virtual void draw(void);

    void appendLine(CCPoint pt1, CCPoint pt2, float r = 1, float g = 1, float b = 1);
    void appendPoint(float x, float y, float r = 1, float g = 1, float b = 1);
    void appendPoint(CCPoint pt, float r = 1, float g = 1, float b = 1);

private:
    std::vector<DebugLine>* m_lines;
    std::vector<DebugPoint>* m_points;
};