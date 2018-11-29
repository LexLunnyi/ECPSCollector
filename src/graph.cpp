#include "graph.h"


void MyGraph::render(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    wxClientDC dc(pWindow);
    dc.SetPen(*pPen);
    dc.SetBrush(*pBrush);
    
    wxRect rectToDraw(x, y, w, h);
    // For efficiency, do not draw if not exposed
    //if (IsExposed(rectToDraw))
    dc.DrawRectangle(rectToDraw);
}