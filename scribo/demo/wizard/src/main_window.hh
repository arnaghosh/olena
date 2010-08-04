// Copyright (C) 2010 EPITA Research and Development Laboratory (LRDE)
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

#ifndef SCRIBO_DEMO_WIZARD_SRC_MAIN_WINDOW_HH
# define SCRIBO_DEMO_WIZARD_SRC_MAIN_WINDOW_HH

# include <QtGui/QWizard>
//# include <ui_main_window.h>

namespace scribo
{

  namespace demo
  {

    namespace wizard
    {


      class main_window : public QWizard
      {
	Q_OBJECT;

      public:
	main_window();

	virtual int nextId() const;

      private slots:
	void showCustomButton_slot(int id);

      private:
	enum { Page_Load,
	       Page_Task,
	       Page_Crop,
	       Page_Rotate,
	       Page_Preprocessing,
	       Page_Process,
	       Page_Result };
      };


    } // end of namespace scribo::demo::wizard

  } // end of namespace scribo::demo

} // end of namespace scribo


#endif // ! SCRIBO_DEMO_WIZARD_SRC_MAIN_WINDOW_HH