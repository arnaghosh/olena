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

#ifndef MLN_FUN_L2L_WRAP_HH
# define MLN_FUN_L2L_WRAP_HH

/// \file mln/fun/l2l/wrap.hh
///
/// Function to wrap labels such as 0 -> 0 and [1, lmax] maps to [1,
/// Lmax] (using modulus).
///
/// \todo Prefer not to cast towards 'unsigned long'; use a procedure
/// such as enc(l) that can work on 'unsigned', 'int_u8', 'label<n>', and
/// also other label types.

# include <mln/core/concept/function.hh>


namespace mln
{

  namespace fun
  {

    namespace l2l
    {

      template <typename L>
      struct wrap : public Function_l2l< wrap<L> >
      {
      public:

	typedef L result;

	template <typename L_>
	L operator()(const L_& l_) const;

      };


# ifndef MLN_INCLUDE_ONLY

      template <typename L>
      template <typename L_>
      inline
      L
      wrap<L>::operator()(const L_& l_) const
      {
	mlc_converts_to(L_, unsigned long)::check();
	unsigned long l = static_cast<unsigned long>(l_);
	return l == 0ul ? L(0ul) : L(1 + (l - 1) % 255);
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::fun::l2l

  } // end of namespace mln::fun

} // end of namespace mln


#endif // ! MLN_FUN_L2L_WRAP_HH
