// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_WIN_CUBE3D_HH
# define MLN_WIN_CUBE3D_HH

/*! \file mln/win/cube3d.hh
 *
 * \brief Definition of the mln::win::cube3d window.
 */

# include <mln/core/internal/classical_window_base.hh>
# include <mln/core/alias/dpoint3d.hh>


namespace mln
{

  mln_internal_add_classical_window_trait(cube3d);


  namespace win
  {

    /*! \brief Cube window defined on the 3D grid.
     *
     * An cube3d is centered and symmetric; so
     * its height (length) is odd.
     *
     * For instance: \n
     *   o o o \n
     *  o o o \n
     * o o o \n

     *   o o o \n
     *  o x o \n
     * o o o \n

     *   o o o \n
     *  o o o \n
     * o o o \n
     * is defined with length = 3.
     */
    struct cube3d : public internal::classical_window_base< dpoint3d, cube3d >
    {
      /*! \brief Constructor.
       *
       * \param[in] length Length, thus height, of the cube3d.
       *
       * \pre \p length is odd.
       */
      cube3d(unsigned length);

      /*! \brief Give the cube length, that is, its height.
       */
      unsigned length() const;

      /*! \brief Give the maximum coordinate gap between the window
       * center and a window point.
       */
      unsigned delta_() const;

      void print_(std::ostream& ostr) const;

    protected:
      unsigned length_;
    };



# ifndef MLN_INCLUDE_ONLY

    inline
    cube3d::cube3d(unsigned length)
      : length_(length)
    {
      mln_precondition(length % 2 == 1);
      const int dind = length / 2;
      for (int sli = - dind; sli <= dind; ++sli)
	for (int row = - dind; row <= dind; ++row)
	  for (int col = - dind; col <= dind; ++col)
	    insert(dpoint3d(sli, row, col));
    }

    inline
    unsigned cube3d::length() const
    {
      return length_;
    }

    inline
    unsigned cube3d::delta_() const
    {
      return length_ / 2;
    }

    inline
    void cube3d::print_(std::ostream& ostr) const
    {
      ostr << "[cube3d: length=" << length_ << ']';
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::win

} // end of namespace mln



#endif // ! MLN_WIN_CUBE3D_HH
