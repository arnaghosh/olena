// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_MORPHO_CLOSING_VOLUME_HH
# define MLN_MORPHO_CLOSING_VOLUME_HH

/// \file mln/morpho/closing_volume.hh
/// \brief Morphological volume closing.
///
/// \todo Clean!

# include <mln/morpho/closing_attribute.hh>
# include <mln/accu/volume.hh>


namespace mln
{

  namespace morpho
  {

    /// Morphological volume closing.
    template <typename I, typename N, typename O>
    void closing_volume(const Image<I>& input, const Neighborhood<N>& nbh,
			std::size_t lambda, Image<O>& output);

    template <typename I, typename N>
    mln_concrete(I)
    closing_volume(const Image<I>& input, const Neighborhood<N>& nbh, std::size_t lambda)
    {
      mln_concrete(I) output;
      initialize(output, input);
      closing_volume(input, nbh, lambda, output);
      return output;
    }


# ifndef MLN_INCLUDE_ONLY

    template <typename I, typename N, typename O>
    inline
    void closing_volume(const Image<I>& input, const Neighborhood<N>& nbh,
			std::size_t lambda, Image<O>& output)
    {
      trace::entering("morpho::closing_volume");
      mln_precondition(exact(output).domain() == exact(input).domain());
      // FIXME: Change sig of closing_attribute!
      closing_attribute< accu::volume<I> >(input, nbh, lambda, output);
      trace::exiting("morpho::closing_volume");
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::morpho

} // end of namespace mln


#endif // ! MLN_MORPHO_CLOSING_VOLUME_HH
