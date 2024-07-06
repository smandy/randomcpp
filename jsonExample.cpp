#include "docopt/docopt.h"
#include "printers.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <json/json.h>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

static const char USAGE[] =
    R"(jsonExample.

    Usage:
      jsonExample <filename>

    Options:
      -h --help  Show this screen.
)";

using namespace std;

int main(int argc, const char** argv)
{
    map<string, docopt::value> args =
        docopt::docopt(USAGE, {argv + 1, argv + argc},
                       true,              // show help if requested
                       "jsonExample 1.0", // version string
                       true);             // options first

    auto x = args["<filename>"].asString();
    cout << "filenams is " << x << endl;

    ifstream f(x);
    Json::Value root;
    f >> root;

    // You can also read into a particular sub-value.
    // std::cin >> root["subtree"];

    // Get the value of the member of root named 'encoding',
    // and return 'UTF-8' if there is no such member.
    std::string encoding = root.get("encoding", "UTF-8").asString();

    // Get the value of the member of root named 'plug-ins'; return a 'null' value
    // if there is no such member.
    const Json::Value plugins = root["plug-ins"];

    // Iterate over the sequence elements.
    for (int index = 0; index < plugins.size(); ++index) {
        cout << plugins[index].asString() << endl;
    };

    //  // Try other datatypes. Some are auto-convertible to others.
    //  foo::setIndentLength(root["indent"].get("length", 3).asInt());
    //  foo::setIndentUseSpace(root["indent"].get("use_space", true).asBool());
    //
    //  // Since Json::Value has an implicit constructor for all value types, it
    //  is
    //  // not necessary to explicitly construct the Json::Value object.
    //  root["encoding"] = foo::getCurrentEncoding();
    //  root["indent"]["length"] = foo::getCurrentIndentLength();
    //  root["indent"]["use_space"] = foo::getCurrentIndentUseSpace();
    //
    //  // If you like the defaults, you can insert directly into a stream.
    //  std::cout << root;
    //  // Of course, you can write to `std::ostringstream` if you prefer.
    //
    //  // If desired, remember to add a linefeed and flush.
    //  std::cout << std::endl;
}
