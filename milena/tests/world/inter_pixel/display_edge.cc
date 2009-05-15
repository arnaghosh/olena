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

/// \file tests/world/inter_pixel/display_edge.cc
///
/// Tests on mln::world::inter_pixel::display_edge.


#include <mln/core/var.hh>
#include <mln/core/image/image2d.hh>
#include <mln/level/compare.hh>
#include <mln/world/inter_pixel/immerse.hh>
#include <mln/world/inter_pixel/compute.hh>
#include <mln/world/inter_pixel/display_edge.hh>

#include <mln/world/inter_pixel/neighb2d.hh>
#include <mln/debug/println.hh>



struct d_t : mln::Function_vv2v<d_t>
{
  typedef int result;

  int operator()(int i1, int i2) const
  {
    return std::abs(i2 - i1);
  }
}
  d;



int main()
{
  using namespace mln;

  {
    int vals[] = { 1 } ;

    typedef image2d<int> I;
    I ima = make::image2d(vals);

    using namespace world::inter_pixel;
    typedef image_if<I, is_pixel> Ix;
    Ix imax = immerse(ima);

    mln_VAR(g, compute(imax, d));
    std::cout << g.unmorph_().bbox() << std::endl;

    mln_VAR(out1, display_edge(g.unmorph_(), 0, 1));
    debug::println(out1);
    mln_VAR(out2, display_edge(g.unmorph_(), 0, 2));
    debug::println(out2);
    mln_VAR(out3, display_edge(g.unmorph_(), 0, 3));
    debug::println(out3);
    mln_VAR(out4, display_edge(g.unmorph_(), 0, 4));
    debug::println(out4);
    mln_VAR(out5, display_edge(g.unmorph_(), 0, 5));
    debug::println(out5);
  }

  {
    int vals[] = { 1, 2,
		   3, 4 } ;

    typedef image2d<int> I;
    I ima = make::image2d(vals);

    using namespace world::inter_pixel;
    typedef image_if<I, is_pixel> Ix;
    Ix imax = immerse(ima);

    mln_VAR(g, compute(imax, d));
    std::cout << g.unmorph_().bbox() << std::endl;

    mln_VAR(out1, display_edge(g.unmorph_(), 0, 1));
    debug::println(out1);
    mln_VAR(out2, display_edge(g.unmorph_(), 0, 2));
    debug::println(out2);
    mln_VAR(out3, display_edge(g.unmorph_(), 0, 3));
    debug::println(out3);
    mln_VAR(out4, display_edge(g.unmorph_(), 0, 4));
    debug::println(out4);
    mln_VAR(out5, display_edge(g.unmorph_(), 0, 5));
    debug::println(out5);
  }
}