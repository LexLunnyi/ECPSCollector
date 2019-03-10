#include "graph.h"


void MyGraph::render(GraphSize & size) {
    xPos = size.x;
    yPos = size.y;
    width = size.width;
    height = size.height;
    
    wxRect rectToDraw(xPos, yPos, width, height);
    pDC->DrawRectangle(rectToDraw);
}



void MyGraph::line(uint32_t x_from, uint32_t y_from, uint32_t x_to, uint32_t y_to) {
    pDC->DrawLine(x_from + xPos, y_from + yPos, x_to + xPos, y_to + yPos);
}


void MyGraph::dot(uint32_t x, uint32_t y) {
    pDC->DrawPoint(x + xPos, y + yPos);
}