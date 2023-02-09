class Clipper
{
    static const int LEFT_REGION = 0x01;
    static const int RIGHT_REGION = 0x02;
    static const int BOTTOM_REGION = 0x04;
    static const int TOP_REGION = 0x08;

    static int accept(int c1, int c2)
    {
        return !(c1 | c2);
    }

    static int reject(int c1, int c2)
    {
        return (c1 & c2);
    }

    static void print_region_code(int c)
    {
        std::string cs = "";
        if (c & TOP_REGION)
            cs += "1";
        else
            cs += "0";

        if (c & BOTTOM_REGION)
            cs += "1";
        else
            cs += "0";

        if (c & LEFT_REGION)
            cs += "1";
        else
            cs += "0";

        if (c & RIGHT_REGION)
            cs += "1";
        else
            cs += "0";

        std::cout << cs << std::endl;
    }

    static int get_region_code(float x, float y, float xmin, float ymin, float xmax, float ymax)
    {
        int code = 0x00;
        if (y < ymin)
            code |= TOP_REGION;
        if (y > ymax)
            code |= BOTTOM_REGION;
        if (x < xmin)
            code |= LEFT_REGION;
        if (x > xmax)
            code |= RIGHT_REGION;
        return code;
    }

    static void intersect(int code, float xmin, float ymin, float xmax, float ymax, float &x, float &y, float x1, float y1, float x2, float y2)
    {
        if (code & TOP_REGION)
        {
            x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
            y = ymin;
        }
        else if (code & BOTTOM_REGION)
        {
            x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
            y = ymax;
        }
        else if (code & RIGHT_REGION)
        {
            y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
            x = xmax;
        }
        else if (code & LEFT_REGION)
        {
            y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
            x = xmin;
        }
    }

    static float calculate_slope(float x1, float y1, float x2, float y2)
    {
        return (y2 - y1) / (x2 - x1);
    }

    static void vertical_clip(float &x, float &y, float _x, float m)
    {
        if (m != 0.0f)
            y += (m * (_x - x));
    }

    static void horizontal_clip(float &x, float &y, float _y, float m)
    {
        if (m != 0.0f)
            x += ((_y - y) / m);
    }

    static bool clipTest(float p, float q, float &u1, float &u2)
    {
        if (p < 0.0f)
        {
            float r = q / p;
            if (r > u2)
                return false;
            if (r > u1)
                u1 = r;
        }
        else if (p > 0.0f)
        {
            float r = q / p;
            if (r < u1)
                return false;
            if (r < u2)
                u2 = r;
        }
        else
        {
            if (q < 0.0f)
            {
                // p = 0 and q < 0 => Outside boundary
                return false;
            }
        }
        return true;
    }

public:
    static bool liang_barsky(float xmin, float ymin, float xmax, float ymax, float &x1, float &y1, float &x2, float &y2)
    {
        float u1 = 0.0f, u2 = 1.0f;

        float dx = x2 - x1;
        float dy = y2 - y1;

        if (clipTest(-dx, x1 - xmin, u1, u2))
        {
            if (clipTest(dx, xmax - x1, u1, u2))
            {
                if (clipTest(-dy, y1 - ymin, u1, u2))
                {
                    if (clipTest(dy, ymax - y1, u1, u2))
                    {
                        if (u2 < 1.0f)
                        {
                            x2 = x1 + u2 * dx;
                            y2 = y1 + u2 * dy;
                        }
                        if (u1 > 0.0f)
                        {
                            x1 = x1 + u1 * dx;
                            y1 = y1 + u1 * dy;
                        }
                        return true;
                    }
                }
            }
        }

        return false;
    }

    static bool cohen_sutherland(float xmin, float ymin, float xmax, float ymax, float &x1, float &y1, float &x2, float &y2)
    {
        bool done = false;
        bool canPlot = false;

        float m = 0.0f;
        int c1 = get_region_code(x1, y1, xmin, ymin, xmax, ymax);
        int c2 = get_region_code(x2, y2, xmin, ymin, xmax, ymax);

        while (!done)
        {
            if (accept(c1, c2))
            {
                done = true;
                canPlot = true;
            }
            else if (reject(c1, c2))
            {
                done = true;
            }
            else
            {
                float x = x1, y = y1;

                if (c1 != 0)
                {
                    intersect(c1, xmin, ymin, xmax, ymax, x, y, x1, y1, x2, y2);
                    x1 = x;
                    y1 = y;
                    c1 = get_region_code(x1, y1, xmin, ymin, xmax, ymax);
                }
                else
                {
                    intersect(c2, xmin, ymin, xmax, ymax, x, y, x1, y1, x2, y2);
                    x2 = x;
                    y2 = y;
                    c2 = get_region_code(x2, y2, xmin, ymin, xmax, ymax);
                }
            }
        }

        return canPlot;
    }
};

class Line
{
public:
    static void draw(float x1, float y1, float x2, float y2)
    {
        float x = x1;
        float y = y1;

        float dx = abs(x1 - x2);
        float dy = abs(y1 - y2);

        int sx = (x2 - x1) / abs(x1 - x2);
        int sy = (y2 - y1) / abs(y1 - y2);

        bool interchange = false;
        if (dy > dx)
        {
            float temp = dx;
            dx = dy;
            dy = temp;
            interchange = true;
        }

        float p = 2 * dy - dx;
        float a = 2 * dy;
        float b = 2 * dy - 2 * dx;

        glBegin(GL_POINTS);
        for (int i = 0; i < dx; i++)
        {
            if (p < 0)
            {
                if (interchange)
                    y += sy;
                else
                    x += sx;
                p += a;
            }
            else
            {
                y += sy;
                x += sx;
                p += b;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    // clipper mode - 0 => Liang Barsky
    // clipper mode - 1 => Cohen Sutherland
    static void draw(float x1, float y1, float x2, float y2, float xmin, float ymin, float xmax, float ymax, int mode)
    {
        switch (mode)
        {
        case 0:
            if (Clipper::liang_barsky(xmin, ymin, xmax, ymax, x1, y1, x2, y2))
                draw(x1, y1, x2, y2);
            break;
        case 1:
            if (Clipper::cohen_sutherland(xmin, ymin, xmax, ymax, x1, y1, x2, y2))
                draw(x1, y1, x2, y2);
            break;
        default:
            draw(x1, y1, x2, y2);
            break;
        }
    }
};
