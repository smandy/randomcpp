template <typename T>
struct Trait1 {
    void foo() {
        static_cast<T*>(this)->foo();
    }
};

template <typename T>
struct Trait2 {
    void bar() {
        static_cast<T*>(this)->bar();
    }
};

struct MyClass : Trait1<MyClass>, Trait2<MyClass> {
    void foo() {
        // implementation of foo
    }

    void bar() {
        // implementation of bar
    }
};

int main() {
    MyClass obj;
    obj.foo();
    obj.bar();
}
