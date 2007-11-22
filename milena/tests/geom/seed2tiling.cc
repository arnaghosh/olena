// Copyright (C) 2007 EPITA Research and Development Laboratory
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

/*! \file tests/geom/seed2tiling.cc
 *
 * \brief Tests on mln::geom::seed2tiling.
 */


# include <mln/core/image2d.hh>
# include <mln/core/neighb2d.hh>
# include <mln/geom/seeds2tiling.hh>
# include <mln/level/compare.hh>

int main()
{
  using namespace mln;

  unsigned vs [16][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  unsigned ws [16][16] = {
    {1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,2 ,2},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3},
    {1 ,1 ,1 ,1 ,1 ,1 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3}
  };

  image2d<unsigned> ima (make::image2d(vs));
  image2d<unsigned> out = geom::seeds2tiling(ima, c4());
  image2d<unsigned> ref (make::image2d(ws));
  mln_assertion (ref == out);
}
