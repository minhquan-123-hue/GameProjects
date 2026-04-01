#include <iostream>
#include <cmath>

struct Vector
{
    int x;
    int y;
};
float square_root(int canh_doi, int canh_ke);

int main()
{
    Vector vector;
    vector.x = 3;
    vector.y = 5;

    float canh_huyen = square_root(vector.y, vector.x);
    std::cout << "canh_huyen: " << canh_huyen << std::endl; // tuc la do dai cua vector
    return 0;
}

float square_root(int canh_doi, int canh_ke)
{
    int canh_huyen; // cạnh huyền chưa căn bậc hai

    canh_huyen = (canh_doi * canh_doi) + (canh_ke * canh_ke);
    std::cout << "cạnh huyền chưa dùng căn bậc 2: " << canh_huyen << std::endl;

    return sqrt(canh_huyen);
}