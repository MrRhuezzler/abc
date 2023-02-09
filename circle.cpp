class Circle {

    static void plotOtherSegments(Point center, Point p){
        glVertex2f(p.x + center.x, p.y + center.y);
        glVertex2f(p.y + center.x, p.x + center.y);
        glVertex2f(-p.y + center.x, p.x + center.y);
        glVertex2f(-p.x + center.x, p.y + center.y);
        glVertex2f(-p.x + center.x, -p.y + center.y);
        glVertex2f(-p.y + center.x, -p.x + center.y);
        glVertex2f(p.y + center.x, -p.x + center.y);
        glVertex2f(p.x + center.x, -p.y + center.y);
    }

    public:
    static void draw(Point center, int radius) {
        glBegin(GL_POINTS);
        int p = 1 - radius;
        int x = 0;
        int y = radius;
        plotOtherSegments(center, Point(x, y));
        x += 1;
        while(x <= y) {
            if(p < 0) {
                p += (2 * x) + 1;
            } else {
                p += (2 * x) - (2 * y) + 1;
                y -= 1;
            }
            plotOtherSegments(center, Point(x, y));
            x += 1;
        }
        glEnd();
    }
};
