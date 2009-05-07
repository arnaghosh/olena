// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of the Olena Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License version 2 as published by the
// Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 51 Franklin Street, Fifth Floor,
// Boston, MA 02111-1307, USA.
//
// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

/// \file tests/fun/stat/mahalanobis.cc
///
/// Tests on mln::fun::stat::mahalanobis.

#include <cstdlib>
#include <mln/accu/stat/var.hh>
#include <mln/fun/stat/mahalanobis.hh>


float my_rand(int c)
{
  return (1 + c) * float(std::rand()) / RAND_MAX;
}


int main()
{
  using namespace mln;

  typedef algebra::vec<3,float> vec3f;

  enum { n = 1000 };
  vec3f v[n];

  for (int i = 0; i < n; ++i)
    {
      v[i][0] = my_rand(0);
      v[i][1] = my_rand(1);
      v[i][2] = my_rand(2);
    }
  
  accu::stat::var<vec3f> a;
  for (int i = 0; i < n; ++i)
    a.take(v[i]);

//   vec3f m = a.mean();
//   mln_assertion(m[0] > 0.4 && m[0] < 0.6);
//   mln_assertion(m[1] > 0.9 && m[1] < 1.1);
//   mln_assertion(m[2] > 1.4 && m[2] < 1.6);

  fun::stat::mahalanobis<vec3f> f(a.variance(), a.mean());

//   algebra::mat<3,3,float> s_1 = a.variance()._1();
//   mln_assertion(s_1(0,0) > 11  && s_1(0,0) < 13);
//   mln_assertion(s_1(1,1) >  2  && s_1(1,1) <  4);
//   mln_assertion(s_1(2,2) > 1.1 && s_1(2,2) < 1.5);
}
