#define BOOST_TEST_MODULE geometry_toolbox
#include <boost/test/included/unit_test.hpp>

#include "slau.h"

BOOST_AUTO_TEST_CASE(slau_test)
{
  const matrix_extended system = {{{{1.,2.,3.}},
                                   {{4.,5.,6.}}}};
  const column result_analyt = {{-1.,2.}};

  const slau test_slau (system);
  const column result_calced = test_slau.solve ();

  BOOST_TEST(test_slau.is_consistent () == true);
  BOOST_TEST(result_analyt == result_calced);
}
