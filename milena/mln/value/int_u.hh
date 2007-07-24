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

#ifndef MLN_VALUE_INT_U_HH
# define MLN_VALUE_INT_U_HH

/*! \file mln/value/int_u.hh
 *
 * \brief Define a generic class for unsigned integers.
 */

# include <mln/metal/math.hh>
# include <mln/value/internal/value_like.hh>
# include <mln/value/internal/encoding.hh>
# include <mln/value/props.hh>
# include <mln/value/set.hh>
# include <mln/debug/format.hh>


namespace mln
{

  namespace value
  {


    /*! \brief Unsigned integer value class.
     *
     * The parameter is \c n the number of encoding bits.
     */
    template <unsigned n>
    struct int_u
      : public internal::value_like_< typename internal::encoding_int_u_<n>::ret,
				      int_u<n> >
    {
    protected:
      typedef internal::value_like_< typename internal::encoding_int_u_<n>::ret,
				     int_u<n> > super;

    public:

      /// Encoding associated type.
      typedef typename super::enc enc;

      /// Constructor without argument.
      int_u();

      /// Constructor from an integer.
      int_u(int i);

      /// Zero value.
      static const int_u<n> zero;

      /// Unit value.
      static const int_u<n> one;
    };


    // Safety.
    template <> struct int_u<0>;
    template <> struct int_u<1>;



    template <unsigned n>
    struct props< int_u<n> >
    {
      static const std::size_t card = metal::pow<2, n>::value;
      static const int_u<n> min; // = 0
      static const int_u<n> max; // = card - 1
      static const unsigned nbits = n;
      typedef data_kind kind;
    };



    /*! \brief Print an unsigned integer \p i into the output stream \p ostr.
     *
     * \param[in,out] ostr An output stream.
     * \param[in] i An unsigned integer.
     *
     * \return The modified output stream \p ostr.
     */
    template <unsigned n>
    std::ostream& operator<<(std::ostream& ostr, const int_u<n>& i);


# ifndef MLN_INCLUDE_ONLY

    template <unsigned n>
    int_u<n>::int_u()
    {
    }

    template <unsigned n>
    int_u<n>::int_u(int i)
    {
      mln_precondition(i >= 0);
      mln_precondition(i <= mln_max(enc));
      this->v_ = enc(i);
    }

    template <unsigned n>
    const int_u<n> int_u<n>::zero = 0;

    template <unsigned n>
    const int_u<n> int_u<n>::one = 1;


    template <unsigned n>
    const int_u<n>
    props< int_u<n> >::min = 0;

    template <unsigned n>
    const int_u<n>
    props< int_u<n> >::max = metal::pow<2, n>::value - 1;

    template <unsigned n>
    std::ostream& operator<<(std::ostream& ostr, const int_u<n>& i)
    {
      return ostr << debug::format(i.to_equiv());
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::value

} // end of namespace mln


#endif // ! MLN_VALUE_INT_U_HH
