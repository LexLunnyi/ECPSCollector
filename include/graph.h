#ifndef GRAPH_H
#define GRAPH_H

#include <wx/window.h>
#include <wx/wx.h>

typedef unsigned __int32 uint32_t;


struct GraphSize {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

class MyGraph {
private:
    wxWindow *pWindow;
    wxClientDC* pDC;
    uint32_t xPos, yPos, width, height;
    const wxPen* pPen;
    const wxBrush* pBrush;
public:
    //wxPen or wxBrush 
    MyGraph(wxWindow* window, const wxPen* curPen, const wxBrush* curBrush) : pWindow(window), pPen(curPen), pBrush(curBrush) {
        pDC = new wxClientDC(pWindow);
        pDC->SetPen(*pPen);
        pDC->SetBrush(*pBrush);
    } 
    virtual ~MyGraph() {};
    
    void render(GraphSize & size);
    void line(uint32_t x_from, uint32_t y_from, uint32_t x_to, uint32_t y_to);
    void dot(uint32_t x, uint32_t y);
    
    uint32_t getHeight() {return height;}
    uint32_t getWidth() {return width;}
};


typedef MyGraph * PMyGraph;


#endif /* GRAPH_H */

