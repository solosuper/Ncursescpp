/*****
 * Copyright Benoit Vey (2015)
 *
 * benoit.vey@etu.upmc.fr
 *
 * This software is a library whose purpose is to provide a RAII-conform
 * interface over the ncurses library.
 *
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 *****/

/**
 * \file Ncurses.cpp
 * \brief Implementation file for the Ncurses class.
 */

#include "Ncurses.hpp"

#include <cassert>

#include "errors.hpp"

namespace nccpp
{

Ncurses::Ncurses()
	: Window{initscr()}, registered_colors_{},
#ifndef NDEBUG
	  windows_{}, is_exit_{false},
#endif
	  colors_initialized_{false}
{
	if (!win_)
		throw errors::NcursesInit{};
}

Ncurses::~Ncurses()
{
	endwin();
	win_ = nullptr;
#ifdef NO_LEAKS
	_nc_freeall();
#endif
}

#ifndef NDEBUG
void Ncurses::register_window_(Window& new_win, Window::Key /*dummy*/)
{
	windows_.push_back(&new_win);
}
#endif

/**
 * \brief Exit ncurses mode and restore normal terminal properties.
 * 
 * \pre %Ncurses mode is on.
 */
void Ncurses::exit_ncurses_mode()
{
	assert(!is_exit_ && "Ncurses mode is already off");
#ifndef NDEBUG
	for (auto elem : windows_)
		elem->invalidate_for_exit_(Window::Key{});
	invalidate_for_exit_(Key{});
	is_exit_ = true;
#endif
	endwin();
}

/**
 * \brief Restore ncurses mode after a call to exit_ncurses_mode().
 * 
 * \pre %Ncurses mode is off.
 */
void Ncurses::resume_ncurses_mode()
{
	assert(is_exit_ && "Ncurses mode is already on");
#ifndef NDEBUG
	for (auto elem : windows_)
		elem->validate_for_resume_(Window::Key{});
	validate_for_resume_(Key{});
	is_exit_ = false;
#endif
	doupdate();
}

} // namespace nccpp
