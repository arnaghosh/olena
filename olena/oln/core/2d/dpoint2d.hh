// Copyright (C) 2001, 2002, 2003, 2004, 2006 EPITA Research and
// Development Laboratory
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

#ifndef OLN_CORE_2D_DPOINT2D_HH
# define OLN_CORE_2D_DPOINT2D_HH

# include <mlc/int.hh>
# include <oln/core/2d/point2d.hh>
# include <oln/core/internal/dpoint_nd.hh>


namespace oln
{

  typedef dpoint2d_<int> dpoint2d;


  /// Super type.
  template<typename C>
  struct set_super_type< dpoint2d_<C> >
  {
    typedef internal::dpoint_nd< dpoint2d_<C> > ret;
  };


  /// Fwd decls.
  template <unsigned D> struct grid_;
  typedef grid_<2> grid2d;
  template <typename C> struct point2d_;
  typedef point2d_<int> point2d;


  /// Virtual types associated to oln::dpoint2d_<C>.
  template <typename C>
  struct vtypes< dpoint2d_<C> >
  {
    typedef grid2d        grid_type;
    typedef point2d       point_type;
    typedef C             coord_type;
    typedef mlc::uint_<2> dim_type;

    typedef mlc::uint_<0> row_comp_type;
    typedef mlc::uint_<1> col_comp_type;
  };


  /// General 2D dpoint class.
  template <typename C>
  class dpoint2d_
    : public internal::dpoint_nd< dpoint2d_<C> >
  {
    typedef dpoint2d_<C>                self_t;
    typedef internal::dpoint_nd<self_t> super_t;

    using super_t::v_;

  public:

    /// Ctor.
    dpoint2d_();

    /// Ctor.
    dpoint2d_(const xtd::vec<2,C>& v);

    /// Ctor.
    dpoint2d_(C row, C col);

    C  row() const;
    C& row();

    C  col() const;
    C& col();
  };



# ifndef OLN_INCLUDE_ONLY

  template <typename C>
  dpoint2d_<C>::dpoint2d_()
  {
  }

  /// Ctor.
  template <typename C>
  dpoint2d_<C>::dpoint2d_(const xtd::vec<2,C>& v)
    : super_t(v)
  {
  }

  /// Ctor.
  template <typename C>
  dpoint2d_<C>::dpoint2d_(C row, C col)
    : super_t(xtd::mk_vec(row, col))
  {
  }

  template <typename C>
  C  dpoint2d_<C>::row() const { return v_[0]; }

  template <typename C>
  C& dpoint2d_<C>::row()       { return v_[0]; }

  template <typename C>
  C  dpoint2d_<C>::col() const { return v_[1]; }

  template <typename C>
  C& dpoint2d_<C>::col()       { return v_[1]; }

# endif


} // end of namespace oln


#endif // ! OLN_CORE_2D_DPOINT2D_HH
