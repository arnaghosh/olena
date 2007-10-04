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

#ifndef MLN_CORE_WIN_LINE_HH
# define MLN_CORE_WIN_LINE_HH

/*! \file mln/core/win/line.hh
 *
 * \brief Definition of the mln::win::line window.
 */

# include <mln/core/concept/window.hh>
# include <mln/core/internal/dpoints_base.hh>
# include <mln/core/dpoint.hh>
# include <mln/core/dpoints_piter.hh>


namespace mln
{

  namespace win
  {
 
    template <typename M, unsigned i, typename E>
    struct line : public Window<E>,
		  public internal::dpoints_base_
      <dpoint_
    <M, int>, point_
       <M, int> >
    {
      /// Point associated type.
      typedef point_<M, int> point;

      /// Dpoint associated type.
      typedef dpoint_<M, int> dpoint;

      /// Point_Iterator type to browse a line forward
      typedef dpoints_fwd_piter<dpoint> fwd_qiter;

      /// Point_Iterator type to browse a line backward
      typedef dpoints_bkd_piter<dpoint> bkd_qiter;

      /// Same as fwd_qiter
      typedef fwd_qiter qiter;

      /*! \brief Constructor.
       *
       * \param[in] length Length of the line.
       *
       * \pre \p length is odd.
       */
      line(unsigned length);

      /*! \brief Test if the window is centered.
       *
       * \return True.
       */
      bool is_centered() const;
	
      /*! \brief Test if the window is symmetric.
       *
       * \return true.
       */
      bool is_symmetric() const;
	
      /*! \brief Give the hline length, that is, its width.
       */
      unsigned length() const;
	
      /*! \brief Give the maximum coordinate gap between the window
       * center and a window point.
       */
      unsigned delta() const;

      /// Apply a central symmetry to the target window.
      E& sym();
		
      protected:
	unsigned length_;
    };


    /*! \brief Print an line window \p win into the output
     *  stream \p ostr.
     *
     * \param[in,out] ostr An output stream.
     * \param[in] win An line window.
     *
     * \return The modified output stream \p ostr.
     *
     * \relates mln::win::line
     */
    template <typename M, unsigned i, typename E>
    std::ostream& operator<<(std::ostream& ostr, const line<M,i,E>& win);

 

# ifndef MLN_INCLUDE_ONLY


    template <typename M, unsigned i, typename E>
    line<M,i,E>::line(unsigned length)
      : length_(length)
    {
      mln_precondition(i < M::dim);
      mln_precondition(length % 2 == 1);
      const int dcol = length / 2;
      for (int col = - dcol; col <= dcol; ++col)
      {
	dpoint n;
	n[i] = col;
	insert(n);
      }
    }

    template <typename M, unsigned i, typename E>
    bool line<M,i,E>::is_centered() const
    {
      return true;
    }

    template <typename M, unsigned i, typename E>
    bool line<M,i,E>::is_symmetric() const
    {
      return true;
    }

    template <typename M, unsigned i, typename E>
    unsigned line<M,i,E>::length() const
    {
      return length_;
    }

    template <typename M, unsigned i, typename E>
    unsigned line<M,i,E>::delta() const
    {
      return length_ / 2;
    }

    template <typename M, unsigned i, typename E>
    E& line<M,i,E>::sym()
    {
      return exact(*this);
    }

    template <typename M, unsigned i, typename E>
    std::ostream& operator<<(std::ostream& ostr, const line<M,i,E>& win)
    {
      ostr << "[line: length=" << win.length() << ']';
      return ostr;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::win

} // end of namespace mln



#endif // ! MLN_CORE_WIN_LINE_HH
