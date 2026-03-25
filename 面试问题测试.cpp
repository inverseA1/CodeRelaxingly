#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const double PI = acos(-1.0);

class POINT {
public:
    double x, y;
    POINT(double x = 0, double y = 0) : x(x), y(y) {}
};

class RECTANGLE {
public:
    double X, Y;
    double length;
    double width;
    double theta;     // rotation angle in degrees

    RECTANGLE(double X, double Y, double l, double w, double theta_deg)
        : X(X), Y(Y), length(l), width(w), theta(theta_deg) {}
};

class SOLUTION {
public:
    bool IORectangle(POINT P, RECTANGLE R) {
        Orthogonalization(P, R);
        double eps = 1e-9;
        if (abs(P.x - R.X) <= R.length / 2 + eps &&
            abs(P.y - R.Y) <= R.width / 2 + eps) {
            return true;
        }
        return false;
    }

    void Orthogonalization(POINT& Point, RECTANGLE& Rectangle) {
        vector<vector<double>> rmat = this->Rotationmatrix(-Rectangle.theta);
        this->MatTimesVec22(rmat, Point.x, Point.y);
        this->MatTimesVec22(rmat, Rectangle.X, Rectangle.Y);
    }

    vector<vector<double>> Rotationmatrix(double theta) {
        vector<vector<double>> rmat = {
            { cos(theta), -sin(theta) },
            { sin(theta),  cos(theta) }
        };
        return rmat;
    }

    void MatTimesVec22(vector<vector<double>> rmat, double& x, double& y) {
        vector<double> point = { x, y };
        x = rmat[0][0] * point[0] + rmat[0][1] * point[1];
        y = rmat[1][0] * point[0] + rmat[1][1] * point[1];
    }
};

double deg2rad(double deg) {
    return deg * PI / 180.0;
}

struct TestCase {
    string name;
    POINT point;
    RECTANGLE rect;
    bool expected;
};

void runTest(const TestCase& test) {
    SOLUTION sol;
    POINT p = test.point;
    RECTANGLE r(test.rect.X, test.rect.Y, test.rect.length, test.rect.width, deg2rad(test.rect.theta));
    bool result = sol.IORectangle(p, r);

    cout << "Test: " << test.name << "\n";
    cout << "  Point (" << test.point.x << ", " << test.point.y << ")\n";
    cout << "  Rect: center(" << test.rect.X << ", " << test.rect.Y << "), size("
         << test.rect.length << ", " << test.rect.width << "), angle " << test.rect.theta << " deg\n";
    cout << "  Expected: " << (test.expected ? "Inside" : "Outside")
         << ", Got: " << (result ? "Inside" : "Outside") << "\n";
    if (result == test.expected) {
        cout << "  PASS\n";
    } else {
        cout << "  FAIL\n";
    }
    cout << "----------------------------------------\n";
}

int main() {
    runTest({
        "Inside, no rotation",
        POINT(2, 3),
        RECTANGLE(0, 0, 10, 8, 0),
        true
    });

    runTest({
        "Outside, no rotation",
        POINT(6, 5),
        RECTANGLE(0, 0, 10, 8, 0),
        false
    });

    runTest({
        "Inside, 45 deg rotation",
        POINT(1, 1),
        RECTANGLE(0, 0, 2*sqrt(2), 2*sqrt(2), 45),
        true
    });

    runTest({
        "Outside, 45 deg rotation",
        POINT(1.5, 1.5),
        RECTANGLE(0, 0, 2*sqrt(2), 2*sqrt(2), 45),
        false
    });

    runTest({
        "Inside, offset center, 30 deg",
        POINT(3, 4),
        RECTANGLE(2, 2, 4, 2, 30),
        true
    });

    runTest({
        "Outside, offset center, 30 deg",
        POINT(5, 5),
        RECTANGLE(2, 2, 4, 2, 30),
        false
    });

    runTest({
        "On boundary (top edge), no rotation",
        POINT(0, 4),
        RECTANGLE(0, 0, 10, 8, 0),
        true
    });

    runTest({
        "Inside, asymmetric, 60 deg",
        POINT(2.5, 1.8),
        RECTANGLE(0, 0, 6, 2, 60),
        true
    });

    runTest({
        "Outside, asymmetric, 60 deg",
        POINT(3.5, 2.0),
        RECTANGLE(0, 0, 6, 2, 60),
        false
    });

    runTest({
        "Inside, angle near 180 deg",
        POINT(1, 0),
        RECTANGLE(0, 0, 4, 2, 179),
        true
    });

    return 0;
}