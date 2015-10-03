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

#ifndef NCURSESCPP_WINDOW_IPP_
#define NCURSESCPP_WINDOW_IPP_

namespace nccpp
{

#include <cassert>

/**
 * \brief Get the managed window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The managed window.
 */
inline WINDOW* Window::get_handle()
{
	assert(win_ && "Window doesn't manage any object");
	return win_;
}

/**
 * \brief Get an existing subwindow.
 * 
 * \param index Index of the subwindow.
 * \pre The Window manages a ncurses window.
 * \pre *index* is a valid subwindow index.
 * \return The subwindow.
 */
inline Subwindow& Window::get_subwindow(std::size_t index)
{
	assert(win_ && "Window doesn't manage any object");
	assert(index < subwindows_.size() && subwindows_[index].win_ && "Invalid subwindow");
	return subwindows_[index];
}

} // namespace nccpp

#include "Window_appearance.ipp"
#include "Window_attributes.ipp"
#include "Window_input.ipp"
#include "Window_misc.ipp"
#include "Window_options.ipp"
#include "Window_output.ipp"

#endif // Header guard