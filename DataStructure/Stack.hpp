#include <iostream>

constexpr int MAX_SIZE = 10;

// User-Defined
class Stack
{
    int stack[MAX_SIZE];
    int noOfElem;
    
    public:
        Stack() : noOfElem(0) {}
        bool push(int val)
        {
            if (MAX_SIZE == noOfElem)
            {
                std::cout << "Overflow!" << std::endl;
                return false;
            }
            else
            {
                stack[noOfElem++] = val;
                return true;
            }
        }
        bool pop()
        {
            if(0 == noOfElem)
            {
                std::cout << "Underflow!" << std::endl;
                return false;
            }
            else
            {
                noOfElem--;
                return true;
            }
        }
        int top()
        {
            if(MAX_SIZE == noOfElem || 0 == noOfElem)
                return -1;
            return stack[noOfElem-1];
        }
};

void userdefinedStack()
{
    std::cout << "User Defined Stack!" << std::endl;
    Stack st;
    st.push(1);
    st.push(2);
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;    
    st.push(3);
    std::cout << st.top() << std::endl;
    st.pop();
    st.pop();
    std::cout << st.top() << std::endl;
    st.pop();
}

// C++ STL
#include <stack>
#include <utility>

struct emplaceTest
{
    int id;
    float val;
    emplaceTest(int i, float f) : id(i), val(f) {}
};


void stlStack()
{
    std::cout << "STL Stack!" << std::endl;
    std::stack<int> st;
    std::stack<int> st2;
    std::stack<int> st3;
    st.push(1);
    st.push(2);
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;    
    st.push(3);
    std::cout << st.top() << std::endl;

    st2.swap(st);

    st.pop();
    st.pop();
    st.pop(); 
    std::cout << "ST2: " << st2.top() << std::endl;

    st3 = st2; // copy constructor called
    //st3 = std::forward<std::stack<int>>(st2); // move semantic gets called: Segmentation fult for st2.top()
    std::cout << "ST2: " << st2.top() << std::endl;
    std::cout << "ST3: " << st3.top() << std::endl;


    std::stack<emplaceTest> st4;
    st4.emplace(1,2.0);
    st4.emplace(2,4.0);    
    std::cout << "ST4: " << st4.top().val << std::endl;

    
}




int main() {
    // Write C++ code here
    //userdefinedStack();
    stlStack();
    return 0;
}
