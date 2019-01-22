#include "graph.h"


void MyGraph::render(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    wxClientDC dc(pWindow);
    dc.SetPen(*pPen);
    dc.SetBrush(*pBrush);
    
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    
    wxRect rectToDraw(xPos, yPos, width, height);
    dc.DrawRectangle(rectToDraw);
}



void MyGraph::line(uint32_t x_from, uint32_t y_from, uint32_t x_to, uint32_t y_to) {
    wxClientDC dc(pWindow);
    dc.SetPen(*pPen);
    dc.SetBrush(*pBrush);
    dc.DrawLine(x_from + yPos, y_from + xPos, x_to + yPos, y_to + xPos);
}