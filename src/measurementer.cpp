#include "measurementer.hpp"
#include <gpio.hpp>

Measurementer::Measurementer(unsigned int pin, unsigned int training, double timeout_sec, unsigned int timeunit_microsec) :
  m_pin(pin),
  m_config(training, timeunit_microsec, timeout_sec)
{
  m_gpio = new Gpio();
}


Measurementer::Measurementer(unsigned int pin, const Measurementer::Config& config) :
  m_pin(pin),
  m_config(config)
{
}

Measurementer::~Measurementer(){
  delete m_gpio;
}

void Measurementer::measure(){
  setup_gpio();
}

void Measurementer::setup_gpio(){
  m_gpio->set_fsel(m_pin, Gpio::FunctionSelect::IN);
}
