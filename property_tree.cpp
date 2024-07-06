#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <string>

namespace pt = boost::property_tree;

int main()
{
    pt::ptree tree;
    pt::read_json("doit.js", tree);
    // std::cout << tree << std::endl;
    std::vector<std::string> m_modules;

    // Use the throwing version of get to find the debug filename.
    // If the path cannot be resolved, an exception is thrown.
    auto m_file = tree.get<std::string>("filename");

    // Use the default-value version of get to find the debug level.
    // Note that the default value is used to deduce the target type.
    auto m_level = tree.get("level", 0);

    // Use get_child to find the node containing the modules, and iterate over
    // its children. If the path cannot be resolved, get_child throws.
    // A C++11 for-range loop would also work.
    for (auto& v : tree.get_child("modules")) {
        // The data function is used to access the data stored in a node.
        m_modules.push_back(v.second.data());
        std::cout << v.second.data() << std::endl;
    }
}
