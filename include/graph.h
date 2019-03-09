#ifndef GRAPH_H
#define GRAPH_H

#include <wx/window.h>
#include <wx/wx.h>

typedef unsigned __int32 uint32_t;


struct GraphSize {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
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
    
    uint32_t getHeight() {return height;}
};


typedef MyGraph * PMyGraph;


#endif /* GRAPH_H */

