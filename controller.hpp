/******************************************************************************
 *          _     _     __                           ___                      *
 *        /' \  /' \  /'__`\                        /\_ \                     *
 *    __ /\_, \/\_, \/\ \/\ \             ___    ___\//\ \     ___   _ __     *
 *  /'_ `\/_/\ \/_/\ \ \ \ \ \  _______  /'___\ / __`\\ \ \   / __`\/\`'__\   *
 * /\ \L\ \ \ \ \ \ \ \ \ \_\ \/\______\/\ \__//\ \L\ \\_\ \_/\ \L\ \ \ \/    *
 * \ \____ \ \ \_\ \ \_\ \____/\/______/\ \____\ \____//\____\ \____/\ \_\    *
 *  \/___L\ \ \/_/  \/_/\/___/           \/____/\/___/ \/____/\/___/  \/_/    *
 *    /\____/                                                                 *
 *    \_/__/                                                                  *
 *                                                                            *
 * Copyright (C) 2015                                                         *
 * Marian Triebe  <marian.triebe  (at) haw-hamburg.de>                        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <usb.h>

#include <cstdint>

#include "args.hpp"

namespace g110 {

struct controller {

  controller() = delete;

  /**
   * Creates a controller for usb device with vendor id `vid`
   * and product id `pid`
   * @param `args` arguments from command line
   **/
  controller(args&& arg);

  /**
   * Kick off controller
   **/
  void run();

  /**
   * Checks if the controller is still running and valid
   **/
  inline bool valid() const { return static_cast<bool>(m_handle); }

 private:
  /**
   * Searches the USB device and gets a handle to device
   * called from ctor
   */
  void init();

  /**
   * Writes `data` to device
   * @returns `true` if expected amount of data has been written
   *          `false` if write was not complete
   **/
  bool write(char data[]);

  struct usb_dev_handle* m_handle;
  args m_args;
};

} // namespace g110

#endif // CONTROLLER_HPP
