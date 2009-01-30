// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_CORE_IMAGE_P2P_IMAGE_HH
# define MLN_CORE_IMAGE_P2P_IMAGE_HH

/// \file mln/core/image/p2p_image.hh
///
/// Definition of a image FIXME: Doc!

# include <mln/core/internal/image_domain_morpher.hh>
# include <mln/core/concept/function.hh>
# include <mln/accu/bbox.hh>


namespace mln
{

  // Forward declaration.
  template <typename I, typename F> struct p2p_image;


  namespace internal
  {

    /// Data structure for \c mln::p2p_image<I,F>.
    template <typename I, typename F>
    struct data< p2p_image<I,F> >
    {
      data(I& ima, const F& f);

      I ima_;
      F f_;
      mln_pset(I) b_;
    };

  } // end of namespace mln::internal


  namespace trait
  {

    template <typename I, typename F>
    struct image_< p2p_image<I,F> > : default_image_morpher< I,
							     mln_value(I),
							     p2p_image<I,F> >
    {
      typedef trait::image::category::domain_morpher category;

      typedef trait::image::ext_domain::none      ext_domain;  // No extension of domain.
      typedef trait::image::ext_value::irrelevant ext_value;
      typedef trait::image::ext_io::irrelevant    ext_io;

      typedef trait::image::vw_io::none                    vw_io;
      typedef trait::image::vw_set::none                   vw_set;
      typedef trait::image::value_alignement::not_aligned  value_alignement;
      typedef trait::image::value_storage::disrupted       value_storage;
    };

  } // end of namespace mln::trait



  /// FIXME: Doc!
  template <typename I, typename F>
  struct p2p_image : public internal::image_domain_morpher< I,
							    mln_pset(I),
							    p2p_image<I, F> >
  {
    /// Skeleton.
    typedef p2p_image< tag::image_<I>, tag::function_<F> > skeleton;

    /// Constructor without argument.
    p2p_image();

    /// Constructor from an image \p ima and a predicate \p f.
    p2p_image(I& ima, const F& f);

    void init_(I& ima, const F& f);

    /// Give the definition domain.
    const mln_pset(I)& domain() const;

    /// Give the p2p function.
    const F& fun() const;

    /// Read-only access to the image value located at point \p p.
    mln_rvalue(I) operator()(const mln_psite(I)& p) const;

    /// Read-write access to the image value located at point \p p.
    mln_morpher_lvalue(I) operator()(const mln_psite(I)& p);
  };



  /// FIXME: Doc!
  template <typename I, typename F>
  p2p_image<I,F>
  apply_p2p(Image<I>& ima, const Function_p2p<F>& f);

  /// FIXME: Doc!
  template <typename I, typename F>
  p2p_image<const I,F>
  apply_p2p(const Image<I>& ima, const Function_p2p<F>& f);



# ifndef MLN_INCLUDE_ONLY

  // init_.

  template <typename I, typename F>
  void init_(tag::function_t, F& f, const p2p_image<I,F>& model)
  {
    f = model.fun();
  }

  template <typename I, typename F, typename J>
  void init_(tag::image_t, p2p_image<I,F>& target, const J& model)
  {
    I ima;
    init_(tag::image, ima, exact(model));
    F f;
    init_(tag::function, f, exact(model));
    target.init_(ima, f);
  }

  // internal::data< p2p_image<I,F> >

  namespace internal
  {

    template <typename I, typename F>
    inline
    data< p2p_image<I,F> >::data(I& ima, const F& f)
      : ima_(ima),
	f_(f)
    {
      accu::bbox<mln_site(I)> a;
      mln_pset(I) b = ima.domain();
      a.take(f(b.pmin()));
      a.take(f(b.pmax()));
      b_ = a.to_result();
      mln_invariant(b_.nsites() == b.nsites());
    }

  }


  // p2p_image<I,F>

  template <typename I, typename F>
  inline
  p2p_image<I,F>::p2p_image()
  {
  }

  template <typename I, typename F>
  inline
  p2p_image<I,F>::p2p_image(I& ima, const F& f)
  {
    init_(ima, f);
  }

  template <typename I, typename F>
  inline
  void
  p2p_image<I,F>::init_(I& ima, const F& f)
  {
    mln_precondition(! this->is_valid());
    this->data_ = new internal::data< p2p_image<I,F> >(ima, f);
  }

  template <typename I, typename F>
  inline
  const mln_pset(I)&
  p2p_image<I,F>::domain() const
  {
    mln_precondition(this->is_valid());
    return this->data_->b_;
  }

  template <typename I, typename F>
  inline
  const F&
  p2p_image<I,F>::fun() const
  {
    mln_precondition(this->is_valid());
    return this->data_->f_;
  }

  template <typename I, typename F>
  inline
  mln_rvalue(I)
  p2p_image<I,F>::operator()(const mln_psite(I)& p) const
  {
    mln_precondition(this->has(p));
    mln_invariant(this->data_->ima_.has(this->data_->f_.inverse(p)));
    return this->data_->ima_(this->data_->f_.inverse(p));
  }

  template <typename I, typename F>
  inline
  mln_morpher_lvalue(I)
  p2p_image<I,F>::operator()(const mln_psite(I)& p)
  {
    mln_precondition(this->has(p));
    mln_invariant(this->data_->ima_.has(this->data_->f_.inverse(p)));
    return this->data_->ima_(this->data_->f_.inverse(p));
  }


  // Routines.

  template <typename I, typename F>
  inline
  p2p_image<I,F>
  apply_p2p(Image<I>& ima_, const Function_p2p<F>& f)
  {
    mlc_is_a(mln_pset(I), Box)::check();

    I& ima = exact(ima_);
    mln_precondition(ima.is_valid());

    p2p_image<I,F> tmp(ima, exact(f));
    return tmp;
  }

  template <typename I, typename F>
  inline
  p2p_image<const I, F>
  apply_p2p(const Image<I>& ima_, const Function_p2p<F>& f)
  {
    mlc_is_a(mln_pset(I), Box)::check();

    const I& ima = exact(ima_);
    mln_precondition(ima.is_valid());

    p2p_image<const I, F> tmp(ima, exact(f));
    return tmp;
  }


# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln



#endif // ! MLN_CORE_IMAGE_P2P_IMAGE_HH