#include "StackByArray.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
    // Creating the Stack on heap memory
    StackByArray* s = new StackByArray(5);
    s->push(10);
    s->push(20);
    s->push(30);
    s->pop();
    s->pop();
    s->peek();
    s->printStack();
    delete s;

    // Creating the Stack on static (stack) memory
    StackByArray st = StackByArray(5);
    st.push(10);
    st.push(20);
    st.peek();
    st.printStack();

    return 0;
}