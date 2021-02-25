#include <boost/program_options.hpp>

namespace po = boost::program_options;

class CommandLineParser{
public:
    CommandLineParser();

    void operator()(int argc, char* argv[]);
    po::variables_map get_variables_map() const { return vm; };

private:
    po::options_description desc;
    po::positional_options_description p;
    po::variables_map vm;

};