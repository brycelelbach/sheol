////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_DB57790F_CE40_4F90_854D_7D6BF482D0D2)
#define SHEOL_DB57790F_CE40_4F90_854D_7D6BF482D0D2

namespace sheol {
namespace adt {

template <std::size_t Numerator, std::size_t Denominator = 1>
struct power_growth_policy {
  typedef std::size_t size_type;

  template <typename T>
  struct apply {
    typedef size_type result_type;

    template <typename Size>
    result_type operator() (Size capacity, Size /*size*/) {
      if (capacity != 0)
        return capacity * (Numerator / Denominator);
      else
        return 1;
    }
  };
};

} // adt
} // sheol

#endif // SHEOL_DB57790F_CE40_4F90_854D_7D6BF482D0D2


