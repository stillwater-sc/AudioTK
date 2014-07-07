/**
 * \ file GainExpanderFilter.cpp
 */

#include <ATK/Dynamic/GainExpanderFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (64)

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::GainExpanderFilter<float> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(10);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_0_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::GainExpanderFilter<float> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.001f);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_threshold_2_slope_2_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::GainExpanderFilter<float> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_slope(2);
  filter.set_softness(1);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.490775019, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_threshold_2_slope_4_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::GainExpanderFilter<float> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_slope(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.118208125, outdata[i], 0.1);
  }
}
