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

#ifndef MLN_BORDER_MIRROR_HH
# define MLN_BORDER_MIRROR_HH

/*! \file mln/border/mirror.hh
 *
 * \brief FIXME.
 */

# include <mln/core/concept/image.hh>


namespace mln
{

  namespace border
  {

    /*! Mirror the virtual (outer) border of image \p ima with the
     *  (inner) level contents of this image.
     *
     * \param[in,out] ima The image whose border is to be mirrored.
     *
     * \pre \p ima has to be initialized.
     *
     * \todo Implement it + optimize with memset if possible.
     */
    template <typename I>
    void mirror(const Fast_Image<I>& ima);


# ifndef MLN_INCLUDE_ONLY

    template <typename I>
    void mirror(const Fast_Image<I>& ima_)
    {
      const I& ima = exact(ima_);
      mln_precondition(ima_.has_data());
      mln_invariant(0); // FIXME: NYI
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::border

} // end of namespace mln


#endif // ! MLN_BORDER_MIRROR_HH
