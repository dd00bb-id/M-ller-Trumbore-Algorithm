#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

class point {
public:
    double x, y, z;
    point() : x(0), y(0), z(0) {}
    point(double a, double b, double c) : x(a), y(b), z(c) {}
};

// 벡터의 외적을 계산하는 함수
point cross(const point& a, const point& b) {
    return point(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// 벡터의 내적을 계산하는 함수
double dot(const point& a, const point& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 벡터의 차를 계산하는 함수
point sub(const point& a, const point& b) {
    return point(a.x - b.x, a.y - b.y, a.z - b.z);
}

// 삼각형과 직선의 교차 여부를 확인하는 함수
bool linecrossTriangle(const point& start, const point& end,
    const point& A, const point& B, const point& C) {
    constexpr double EPSILON = std::numeric_limits<double>::epsilon();

    // 직선의 방향 벡터
    point rayDirection = sub(end, start);

    // 삼각형의 두 변
    point edge1 = sub(B, A);
    point edge2 = sub(C, A);

    // 교차점 계산
    point h = cross(rayDirection, edge2);
    double a = dot(edge1, h);

    // 레이가 삼각형과 평행한 경우
    if (a > -EPSILON && a < EPSILON) return false;

    double f = 1.0 / a;
    point s = sub(start, A);
    double u = f * dot(s, h);

    // u 값이 범위를 벗어나는 경우
    if (u < 0.0 || u > 1.0) return false;

    point q = cross(s, edge1);
    double v = f * dot(rayDirection, q);

    // v 값이 범위를 벗어나는 경우
    if (v < 0.0 || u + v > 1.0) return false;

    // t 계산
    double t = f * dot(edge2, q);
    return t > EPSILON;  // t가 양수일 경우 교차
}

int main() {
    // 총을 쏘는 위치 입력
    point Q;
    cout << "<총을 쏘는 위치 입력>" << endl;
    cout << "x좌표 : ";
    cin >> Q.x;
    cout << "y좌표 : ";
    cin >> Q.y;
    cout << "z좌표 : ";
    cin >> Q.z;

    // 타겟 위치 입력
    point target;
    cout << "<타겟 위치 입력>" << endl;
    cout << "x좌표 : ";
    cin >> target.x;
    cout << "y좌표 : ";
    cin >> target.y;
    cout << "z좌표 : ";
    cin >> target.z;

    // 삼각형의 세 점 입력
    point A, B, C;
    cout << "<삼각형의 세 점 입력>" << endl;
    cout << "A 점 (x, y, z) : ";
    cin >> A.x >> A.y >> A.z;
    cout << "B 점 (x, y, z) : ";
    cin >> B.x >> B.y >> B.z;
    cout << "C 점 (x, y, z) : ";
    cin >> C.x >> C.y >> C.z;

    // 삼각형과 직선의 교차 여부 확인
    if (linecrossTriangle(Q, target, A, B, C)) {
        cout << "명중!" << endl;
    }
    else {
        cout << "Miss!" << endl;
    }

    return 0;
}
