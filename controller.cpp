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
#include "controller.hpp"

#include <thread>
#include <chrono>
#include <stdexcept>

using u8 = uint8_t;
using namespace g110;
using namespace std;
using namespace std::chrono;

namespace {
  constexpr int ukn1 = 0x21;
  constexpr int ukn2 = 0x00000009;
  constexpr int ukn3 = 0x00000307;
  constexpr int ukn4 = 0;
  constexpr int timeout = 250; // ms
} // namespace <anonymous>

controller::controller(args&& arg)
  : m_handle(nullptr), m_args(std::move(arg)) {
  init();
}

void controller::init() {
  struct usb_device* dev = nullptr;
  struct usb_bus* bus = nullptr;
  usb_init();
  usb_find_busses();
  usb_find_devices();
  bus = usb_get_busses();
  auto find_dev = [&]() {
    auto tmp = bus->devices;
    while (tmp && !dev) {
      if (tmp->descriptor.idVendor == m_args.m_vid &&
          tmp->descriptor.idProduct == m_args.m_pid) {
        dev = tmp;
      }
      tmp = tmp->next;
    }
  };
  while (bus && !dev) {
    find_dev();
    bus = bus->next;
  }
  if (!dev) {
    throw std::runtime_error("Could not find matching device");
  }
  m_handle = usb_open(dev);
  if (!m_handle) {
    throw std::runtime_error("Could not open device");
  }
  usb_detach_kernel_driver_np(m_handle, 0);
  usb_set_configuration(m_handle, 1);
}

bool controller::write(char data[]) {
  return usb_control_msg(m_handle, ukn1, ukn2, ukn3, ukn4, data,
                         sizeof(data), timeout) == sizeof(data);
}

void controller::run() {
  char data[] = {
    0x07, /* unknown */
    0x00, /* color   */
    0x00, /* unknown */
    0x00, /* unknown */
    numeric_limits<char>::max() /* brightness */
  };
  auto update = [&](u8 color) {
    data[1] = color;
    write(data);
    this_thread::sleep_for(milliseconds(m_args.m_refresh_rate));
  };
  if (m_args.m_fixed) {
    // just set once and exit
    update(m_args.m_fixed_color);
    return;
  }
  auto current = m_args.m_begin;
  while (true) {
    while (current < m_args.m_end) {
      update(current++);
    }
    while (current > m_args.m_begin) {
      update(current--);
    }
  }
}
