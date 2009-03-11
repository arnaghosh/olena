// Copyright (C) 2009 EPITA Research and Development Laboratory
// (LRDE)
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


#ifndef SCRIBO_TABLE_INTERNAL_CONNECT_LINES_HH
# define SCRIBO_TABLE_INTERNAL_CONNECT_LINES_HH

/// \file scribo/table/connect_vertical_lines.hh
///
/// Connect vertical lines with aligned rows.

# include <mln/core/image/image1d.hh>

# include <mln/data/fill.hh>

# include <mln/morpho/elementary/dilation.hh>
# include <mln/util/array.hh>
# include <mln/util/couple.hh>

# include <mln/opt/at.hh>

# include <scribo/core/macros.hh>


namespace scribo
{

  namespace table
  {

    namespace internal
    {

      /// Connect vertical and horizontal lines if they are close to each other.
      ///
      ///  ------                 ------
      ///		  --->          |
      ///        |                      |
      ///        |                      |
      ///
      ///
      /// FIXME: doc arguments.
      template <typename P>
      void
      connect_lines(const util::array<int>& aligned_lines,
		    util::array< box<P> >& boxes,
		    unsigned dim,
		    unsigned dim_size);


# ifndef MLN_INCLUDE_ONLY


      template <typename P>
      void
      connect_lines(const util::array<int>& aligned_lines,
		    util::array< box<P> >& boxes,
		    unsigned dim,
		    unsigned dim_size)
      {
	trace::entering("scribo::table::internal::connect_lines");

	image1d<int> l(dim_size);
	data::fill(l, -1);

	for_all_elements(i, aligned_lines)
	  opt::at(l, aligned_lines[i]) = i;

	for (unsigned i = 0; i < settings.max_dist_lines; ++i)
	  l = morpho::elementary::dilation(l, c2());

	for_all_components(i, boxes)
	{
	  util::couple<point2d, point2d> cp = central_sites(boxes[i], dim);
	  if (opt::at(l, cp.first()[dim]) != -1)
	    boxes[i].pmin()[dim] = aligned_lines[opt::at(l, cp.first()[dim])];
	  if (opt::at(l, cp.second()[dim]) != -1)
	    boxes[i].pmax()[dim] = aligned_lines[opt::at(l, cp.second()[dim])];
	}

	trace::exiting("scribo::table::internal::connect_lines");
      }


# endif // ! MLN_INCLUDE_ONLY


  } // end of namespace scribo::table

} // end of namespace scribo


#endif // ! SCRIBO_TABLE_INTERNAL_CONNECT_LINES_HH