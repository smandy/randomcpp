#include <iostream>

// Head of the hammer
class HammerHead {
public:
    void strike() {
        std::cout << "HammerHead: striking!" << std::endl;
    }
};

// Handle of the hammer
class HammerHandle {
public:
    void grip() {
        std::cout << "HammerHandle: gripping!" << std::endl;
    }
};

// Hammer that combines the head and handle
class Hammer {
public:
    Hammer(HammerHead& head, HammerHandle& handle) : m_head(head), m_handle(handle) {}

    void strike() {
        m_head.strike();
    }

    void grip() {
        m_handle.grip();
    }

private:
    HammerHead& m_head;
    HammerHandle& m_handle;
};

// Main function
int main() {
    HammerHead head;
    HammerHandle handle;
    Hammer hammer(head, handle);
    hammer.grip();
    hammer.strike();
    return 0;
}
