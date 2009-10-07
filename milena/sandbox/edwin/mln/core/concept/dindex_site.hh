// Copyright (C) 2008, 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

///
/// \file
///
/// Definition of the concept mln::Dindex_Site
///

#ifndef MLN_CORE_CONCEPT_DINDEX_SITE_HH
# define MLN_CORE_CONCEPT_DINDEX_SITE_HH

namespace mln
{

  // Forward declaration.
  template <typename E> struct Dindex_Site;


  namespace trait
  {

    // FIXME: Add promotion.

    template < typename L, typename R >
    struct set_binary_< op::plus,
			mln::Dindex_Site, L, mln::Dindex_Site, R >
    {
      typedef L ret;
    };

    template < typename L, typename R >
    struct set_binary_< op::minus,
			mln::Dindex_Site, L, mln::Dindex_Site, R >
    {
      typedef L ret;
    };

     template < typename L, typename S>
    struct set_binary_< op::plus,
			mln::Dindex_Site, L, mln::value::Scalar, S >
    {
      typedef L ret;
    };

    template < typename L, typename S>
    struct set_binary_< op::minus,
			mln::Dindex_Site, L, mln::value::Scalar, S >
    {
      typedef L ret;
    };

    template < typename D, typename S >
    struct set_binary_< op::times,
			mln::Dindex_Site, D,
			mln::value::Scalar, S >
    {
      typedef D ret;
    };

    template <typename D>
    struct set_unary_< op::ord, mln::Dindex_Site, D >
    {
      typedef mln::internal::ord_less< D > ret;
    };

  } // end of namespace mln::trait



  /// Delta point site category flag type.
  template <>
  struct Dindex_Site<void>
  {
    typedef Object<void> super;
  };


  /// FIXME: Doc!
  template <typename E>
  struct Dindex_Site : public Object<E>
  {
    typedef Dindex_Site<void> category;

    /*
    typedef value_t;
    typedef site;
    typedef psite;

    const value_t& value();
    void change_value(const value_t&);
    */

  protected:
    Dindex_Site();
  };



  // Operators.

  template <typename D>
  std::ostream&
  operator<<(std::ostream& ostr, const Dindex_Site<D>& dp);

  template <typename L, typename R>
  bool
  operator==(const Dindex_Site<L>& lhs, const Dindex_Site<R>& rhs);


  template <typename L, typename R>
  L operator+(const Dindex_Site<L>& lhs, const Dindex_Site<R>& rhs);

  template <typename L, typename R>
  L operator-(const Dindex_Site<L>& lhs, const Dindex_Site<R>& rhs);

  template <typename L, typename S>
  L operator+(const Dindex_Site<L>& lhs, const value::Scalar<S>& rhs);

  template <typename L, typename S>
  L operator-(const Dindex_Site<L>& lhs, const value::Scalar<S>& rhs);

  template <typename D, typename S>
  D operator*(const Dindex_Site<D>& lhs, const value::Scalar<S>& rhs);


  namespace convert
  {

    namespace over_load
    {

      template <typename D>
      void
      from_to_(const Dindex_Site<D>& from, mln_site(D)& to);

    } // end of namespace mln::convert::over_load

  } // end of namespace mln::convert


# ifndef MLN_INCLUDE_ONLY

  template <typename E>
  inline
  Dindex_Site<E>::Dindex_Site()
  {
    typedef typename E::value_t value_t;
    const value_t& (E::*m)() const = & E::value;
    m = 0;
  }


  template <typename D>
  inline
  std::ostream& operator<<(std::ostream& ostr, const Dindex_Site<D>& dp)
  {
    ostr << '(' << debug::format(exact(dp).value()) << ')';
    return ostr;
  }


  template <typename L, typename R>
  inline
  bool operator==(const Dindex_Site<L>& lhs, const Dindex_Site<R>& rhs)
  {
    return exact(lhs).value() == exact(rhs).value();
  }

  template <typename L, typename R>
  inline
  L operator+(const Dindex_Site<L>& lhs, const Dindex_Site<R>& rhs)
  {
    L tmp(exact(lhs).value() + exact(rhs).value());
    return tmp;
  }

  template <typename L, typename R>
  inline
  L operator-(const Dindex_Site<L>& lhs, const Dindex_Site<R>& rhs)
  {
    L tmp(exact(lhs).value() - exact(rhs).value());
    return tmp;
  }

 template <typename L, typename S>
  inline
  L operator+(const Dindex_Site<L>& lhs, const value::Scalar<S>& rhs)
  {
    L tmp(exact(lhs).value() + exact(rhs).to_equiv());
    return tmp;
  }

  template <typename L, typename S>
  inline
  L operator-(const Dindex_Site<L>& lhs, const value::Scalar<S>& rhs)
  {
    L tmp(exact(lhs).value() - exact(rhs).to_equiv());
    return tmp;
  }

  template <typename D, typename S>
  D operator*(const Dindex_Site<D>& lhs, const value::Scalar<S>& rhs)
  {
    D tmp(exact(lhs).value() * exact(rhs).to_equiv());
    return tmp;
  }

  namespace convert
  {

    namespace over_load
    {

      template <typename D>
      inline
      void
      from_to_(const Dindex_Site<D>& dp, mln_site(D)& p)
      {
	p.change_index(exact(dp).value());
      }

    } // end of namespace mln::convert::over_load

  } // end of namespace mln::convert

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln

#endif // !MLN_CORE_CONCEPT_DINDEX_SITE_HH
