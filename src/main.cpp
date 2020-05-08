#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include "measurementer.hpp"

using namespace std;
namespace po = boost::program_options;

struct CommandLineArgs{
  double timeout;
  int    train;
  int    pin;
  string label;
};

int main(int ac, char* av[])
{

  CommandLineArgs args;

  try {

      po::options_description desc("Options");
      desc.add_options()
          ("help,h", "produce help message")
          ("pin,p", po::value<int>(&args.pin), "[require] gpio pin number")
          ("label,l", po::value<string>(&args.label), "[require] label name(example. -l AC)")
          ("timeout,t", po::value<double>(&args.timeout)->default_value(5.0), "signal timeout second. default 5sec")
          ("train,T", po::value<int>(&args.train)->default_value(10), "training num. default 10")
      ;

      po::variables_map vm;
      po::store(po::parse_command_line(ac, av, desc), vm);
      po::notify(vm);

      if (vm.count("help")) {
          cout << desc << "\n";
          return 0;
      }

      cout << "pin: " << args.pin << endl;
      cout << "label: " << args.label << endl;
      cout << "timeout(sec): " << args.timeout << endl;
      cout << "train: " << args.train << endl;

  }
  catch(exception& e) {
      cerr << "error: " << e.what() << "\n";
      return 1;
  }
  catch(...) {
      cerr << "Exception of unknown type!\n";
  }

  return 0;
}
