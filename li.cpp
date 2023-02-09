class Line {
public:
    static bool clipTest(float p, float q, float& u1, float u2) {
        if(p < 0.0f) {
            float r = q / p;
            if (r > u2) return false;
            if (r > u1) u1 = r;
        } else if(p > 0.0f) {
            float r = q / p;
            if (r < u1) return false;
            if (r < u2) u2 = r;
        } else {
            if (q < 0.0f) {
                // p = 0 and q < 0 => Outside boundary
                return false;
            }
        }
        return true;
    }

    static void liang_barsky_clipper(float xmin, float ymin, float xmax, float ymax, float& x1, float& y1, float& x2, float& y2) {

        float u1 = 0.0f, u2 = 1.0f;

        float dx = x2 - x1;
        float dy = y2 - y1;

        if(clipTest(-dx, x1 - xmin, u1, u2))
            if(clipTest(dx, xmax - x1, u1, u2))
                if(clipTest(-dy, y1 - ymin, u1, u2))
                    if(clipTest(dy, ymax - y1, u1, u2))
                        if(u2 < 1.0f){
                            x2 = x1 + u2 * dx;
                            y2 = y1 + u2 * dy;
                        }
                        if(u1 > 0.0f) {
                            x1 = x1 + u1 * dx;
                            y1 = y1 + u1 * dy;
                        }
    }

    static void draw_without_clipping(float x1, float y1, float x2, float y2) {
        float x = x1;
        float y = y1;

        float dx = abs(x1 - x2);
        float dy = abs(y1 - y2);

        int sx = (x2 - x1) / abs(x1 - x2);
        int sy = (y2 - y1) / abs(y1 - y2);

        bool interchange = false;
        if (dy > dx) {
            float temp = dx;
            dx = dy;
            dy = temp;
            interchange = true;
        }

        float p = 2 * dy - dx;
        float a = 2 * dy;
        float b = 2 * dy - 2 * dx;

        glBegin(GL_POINTS);
        for(int i = 0; i < dx; i++) {
            if (p < 0) {
                if(interchange)
                    y += sy;
                else
                    x += sx;
                p += a;
            } else {
                y += sy;
                x += sx;
                p += b;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    static void draw(float xmin, float ymin, float xmax, float ymax, float x1, float y1, float x2, float y2) {
        // Clip before drawing
        liang_barsky_clipper(xmin, ymin, xmax, ymax, x1, y1, x2, y2);
        draw_without_clipping(x1, y1, x2, y2);
    }
};
