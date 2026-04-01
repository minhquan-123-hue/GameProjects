#include <iostream>

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

    square_root(vector.y, vector.x);
    return 0;
}

float square_root(int canh_doi, int canh_ke)
{
    int canh_huyen; // cạnh huyền chưa căn bậc hai

    canh_huyen = (canh_doi * canh_doi) + (canh_ke * canh_ke);
    std::cout << "cạnh huyền chưa dùng căn bậc 2: " << canh_huyen << std::endl;

    return canh_huyen;
}