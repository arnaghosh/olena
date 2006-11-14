// Copyright (C) 2006 EPITA Research and Development Laboratory
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

#ifndef OLN_CORE_IMAGE_ENTRY_HH
# define OLN_CORE_IMAGE_ENTRY_HH

# include <oln/core/abstract/entry.hh>
# include <oln/core/abstract/image/all.hh>

# include <oln/core/type_fun/plain.hh>



namespace oln
{

  /// Fwd decl.
  template <typename E> struct image_entry;



  /// Virtual types associated to image_entry<E>.

  template <typename E>
  struct vtypes< image_entry<E> >
  {
    typedef mlc::undefined topo_type;
    typedef mlc::undefined grid_type;
    typedef mlc::undefined point_type;
    typedef mlc::undefined is_computed_type;
    typedef mlc::undefined value_type;

    typedef mlc::undefined fwd_piter_type;
    typedef mlc::undefined bkd_piter_type;

    typedef mlc::undefined fwd_qiter_type;
    typedef mlc::undefined bkd_qiter_type;

    // final definitions:
    typedef oln_deduce(E, point, coord) coord_type;
    typedef oln_fwd_piter(E)            piter_type;

    // default definitions:
    typedef oln_point(E) psite_type;
    typedef oln_value(E) rvalue_type;

    /// \brief Morpher type.
    ///
    /// Optionally contains a tag indicating a kind of morpher.
    typedef mlc::none morpher_type;
  };



  /// Entry class for point sets: image_entry<E> is an alias for
  /// entry< abstract::image, E>.

  template <typename E>
  struct image_entry : public entry<abstract::image, E>
  {
  protected:
    image_entry();
  };


# ifndef OLN_INCLUDE_ONLY

  template <typename E>
  image_entry<E>::image_entry()
  {
  }

# endif




} // end of namespace oln


#endif // ! OLN_CORE_IMAGE_ENTRY_HH
