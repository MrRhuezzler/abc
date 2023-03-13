class PloygonClipper
{
    // Inside Outside check
private:
    static std::vector<std::pair<float, float>> clipLeft(const std::vector<std::pair<float, float>> &points, float xmin)
    {
        std::vector<std::pair<float, float>> clipped;
        for (int i = 0, j = 1; i < points.size(); i++, j = (++j) % points.size())
        {
            auto p1 = points[i];
            auto p2 = points[j];

            // out - in
            if (p1.first < xmin && p2.first >= xmin)
            {
                float nX = xmin;
                float m = (p2.second - p1.second) / (p2.first - p1.first);
                float nY = p1.second + ((nX - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
                clipped.push_back(p2);
            }
            // in - in
            else if (p1.first >= xmin && p2.first >= xmin)
            {
                clipped.push_back(p2);
            }
            // in - out
            else if (p1.first >= xmin && p2.first < xmin)
            {
                float nX = xmin;
                float m = (p2.second - p1.second) / (p2.first - p1.first);
                float nY = p1.second + ((nX - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
            }
        }

        return clipped;
    }

    static std::vector<std::pair<float, float>> clipRight(const std::vector<std::pair<float, float>> &points, float xmax)
    {
        std::vector<std::pair<float, float>> clipped;
        for (int i = 0, j = 1; i < points.size(); i++, j = (++j) % points.size())
        {
            auto p1 = points[i];
            auto p2 = points[j];

            // out - in
            if (p1.first > xmax && p2.first <= xmax)
            {
                float nX = xmax;
                float m = (p2.second - p1.second) / (p2.first - p1.first);
                float nY = p1.second + ((nX - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
                clipped.push_back(p2);
            }
            // in - in
            else if (p1.first <= xmax && p2.first <= xmax)
            {
                clipped.push_back(p2);
            }
            // in - out
            else if (p1.first <= xmax && p2.first > xmax)
            {
                float nX = xmax;
                float m = (p2.second - p1.second) / (p2.first - p1.first);
                float nY = p1.second + ((nX - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
            }
        }

        return clipped;
    }

    static std::vector<std::pair<float, float>> clipBottom(const std::vector<std::pair<float, float>> &points, float ymax)
    {
        std::vector<std::pair<float, float>> clipped;
        for (int i = 0, j = 1; i < points.size(); i++, j = (++j) % points.size())
        {
            auto p1 = points[i];
            auto p2 = points[j];

            // out - in
            if (p1.second > ymax && p2.second <= ymax)
            {
                float nY = ymax;
                float m = (nY - p1.second) / (p2.second - p1.second);
                float nX = p1.first + ((p2.first - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
                clipped.push_back(p2);
            }
            // in - in
            else if (p1.second <= ymax && p2.second <= ymax)
            {
                clipped.push_back(p2);
            }
            // in - out
            else if (p1.second <= ymax && p2.second > ymax)
            {
                float nY = ymax;
                float m = (nY - p1.second) / (p2.second - p1.second);
                float nX = p1.first + ((p2.first - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
            }
        }

        return clipped;
    }

    static std::vector<std::pair<float, float>> clipTop(const std::vector<std::pair<float, float>> &points, float ymin)
    {
        std::vector<std::pair<float, float>> clipped;
        for (int i = 0, j = 1; i < points.size(); i++, j = (++j) % points.size())
        {
            auto p1 = points[i];
            auto p2 = points[j];

            // out - in
            if (p1.second < ymin && p2.second >= ymin)
            {
                float nY = ymin;
                float m = (nY - p1.second) / (p2.second - p1.second);
                float nX = p1.first + ((p2.first - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
                clipped.push_back(p2);
            }
            // in - in
            else if (p1.second >= ymin && p2.second >= ymin)
            {
                clipped.push_back(p2);
            }
            // in - out
            else if (p1.second >= ymin && p2.second < ymin)
            {
                float nY = ymin;
                float m = (nY - p1.second) / (p2.second - p1.second);
                float nX = p1.first + ((p2.first - p1.first) * m);

                clipped.push_back(std::make_pair(nX, nY));
            }
        }

        return clipped;
    }

public:
    static std::vector<std::pair<float, float>> sutherland_hodgeman(float xmin, float xmax, float ymin, float ymax, const std::vector<std::pair<float, float>> &points)
    {
        std::vector<std::pair<float, float>> clipped;
        clipped = clipLeft(points, xmin);
        clipped = clipRight(clipped, xmax);
        clipped = clipTop(clipped, ymin);
        clipped = clipBottom(clipped, ymax);

        return clipped;
    }
};
