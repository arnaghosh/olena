// Copyright (C) 2009 EPITA Research and Development Laboratory
// (LRDE)
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


#include <mln/core/image/image2d.hh>
#include <mln/core/alias/box2d.hh>
#include <mln/make/box2d.hh>
#include <mln/util/array.hh>
#include <mln/util/couple.hh>
#include <mln/io/pbm/load.hh>
#include <mln/value/label_8.hh>
#include <mln/win/vline2d.hh>
#include <mln/win/hline2d.hh>
#include <mln/core/alias/neighb2d.hh>

#include <mln/literal/colors.hh>

#include <mln/io/pgm/save.hh>

#include <scribo/extract/primitive/lines_h_discontinued.hh>
#include <scribo/extract/primitive/lines_v_discontinued.hh>

#include <scribo/debug/save_table_image.hh>

#include <scribo/tests/data.hh>

int main(int argc, char *argv[])
{
  using namespace mln;

  std::string img;
  if (argc < 2)
    img = SCRIBO_IMG_DIR "/table_to_be_repaired.pbm";
  else
    img = argv[1];

  image2d<bool> input;
  io::pbm::load(input, img.c_str());

  typedef util::array<box2d> lineboxes_t;

  lineboxes_t
    vboxes,
    hboxes;
  vboxes.append(make::box2d(0,0, 59,59));
  vboxes.append(make::box2d(0,28, 25, 32));
  vboxes.append(make::box2d(33,28, 59,32));
  hboxes.append(make::box2d(0,0, 59,59));
  hboxes.append(make::box2d(27,0, 31, 24));
  hboxes.append(make::box2d(27,36, 31,59));

  value::label_8 nbboxes;

  lineboxes_t hboxes_, vboxes_;

  typedef image2d<value::label_8> lbl_t;
  lbl_t
    hlbl = scribo::extract::primitive::lines_h_discontinued(input, c8(),
							    nbboxes, 11, 2,
							    hboxes_);
  lbl_t
    vlbl = scribo::extract::primitive::lines_v_discontinued(input, c8(),
							    nbboxes, 11, 2,
							    vboxes_);
  mln_assertion(hboxes_ == hboxes);
  mln_assertion(vboxes_ == vboxes);
}
