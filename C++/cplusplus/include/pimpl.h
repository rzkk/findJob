
#ifndef _PIMPL_
#define _PIMPL_


class Line{
public:
    Line(int x1,int y1 , int x2 ,int y2 );
    ~Line();
    void printLine() const; // 打印Line 信息
private:
    class LineImpl;    //内部类的前向声明
    LineImpl * _pimpl;
};


#endif
