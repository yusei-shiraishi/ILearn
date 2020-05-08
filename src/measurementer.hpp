#ifndef MEASUREMENTER_HPP
#define MEASUREMENTER_HPP

class Gpio;

class Measurementer{
public:
  struct Config {
    Config(unsigned int t, unsigned int tu, double to):training(t), timeunit_microsec(tu), timeout_sec(to) {}
    unsigned int training;
    unsigned int timeunit_microsec;
    double timeout_sec;
  };

	Measurementer(unsigned int pin, unsigned int training, double timeout_sec = 5.0, unsigned int timeunit_microsec = 100);
	Measurementer(unsigned int pin, const Config& config);
	~Measurementer();

  void measure();

private:
  const Config m_config;
  unsigned int m_pin;
  Gpio* m_gpio;

  void setup_gpio();
};

#endif
