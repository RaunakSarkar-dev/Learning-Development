#include <iostream>

using namespace std;

template <typename T, int N>
struct Array_type{
    using type = T;
    static const int dim = N;
    const int x = 10;
    static constexpr void show() { cout << "Hello World!!" << endl; }
};

class A{
    
    private:
        int x;
    public:
        A(int x):x(x){};
        void show() const { cout << x << endl;}
        A(A& y) { this->x = y.x;}
        //A(A&& y): x(y.x) { y.x = 0;}
        //A& operator=(A&& y){x = y.x; y.x = 0;}
        ~A() { cout << "Destroyed" << endl;}
};

int main()
{
    using Array = Array_type<int,3>;
    Array::type l;
    constexpr int s = Array::dim;
    int value;
    cout << "Hi: " << s << endl;
    Array::show();
    if(is_polymorphic<string>::value) cout << "Surprise!!" << endl;
    enum class Axis : char {g,o,z};
    enum flags {off,g=1,o=g<<1,z=o<<1};
    
    typename underlying_type<Axis>::type k;
    typename underlying_type<Axis>::type q;
    
    
    A *a1 = new A(10);A *a2 = new A(20);
    a1->show();
    a2->show();
    a1 = move(a2);
    a1->show();
    a2->show();

    return 0;
}
