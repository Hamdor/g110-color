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

#include <getopt.h>

#include <cstdint>
#include <iostream>

#include "args.hpp"

using std::cout;
using std::endl;
using namespace g110;

namespace {

constexpr uint16_t vid = 0x046d; // Logitech
constexpr uint16_t pid = 0xc22b; // G110

enum options {
  fixedcolor = 1,
  begin,
  end,
  refreshrate,
  help
};

const struct option options[] = {
  { "fixed-color",  required_argument, 0, static_cast<char>(fixedcolor)  },
  { "begin",        required_argument, 0, static_cast<char>(begin)       },
  { "end",          required_argument, 0, static_cast<char>(end)         },
  { "refresh-rate", required_argument, 0, static_cast<char>(refreshrate) },
  { "help",         no_argument,       0, static_cast<char>(help)        }
};

} // namespace <anonymous>

void arg_parser::print_help() {
  cout << "Usage: ./g110 [Options]"                               << endl
       << "Options:"                                              << endl
       << "  --fixed-color=<arg>     Set fixed color (0-254)"     << endl
       << "                          254 = Blue"                  << endl
       << "                          127 = Pink"                  << endl
       << "                          0 = Red"                     << endl
       << "  --begin=<arg>           Set beginning color (0-254)" << endl
       << "  --end=<arg>             Set ending color (0-254)"    << endl
       << "  --refresh-rate<arg>     Set the refresh rate"        << endl
       << "  --help                  Show this help message"      << endl;
}

args arg_parser::parse_args(int argc, char* argv[]) {
  args res = { vid, pid, false, 0, 0, 254, 50 };
  int opt = 0;
  int idx = 0;
  auto get_range = [&]() {
    auto tmp = atoi(optarg);
    return tmp >= 0 && tmp <= 254 ? tmp : 0;
  };
  while ((opt = getopt_long_only(argc, argv, "", options, &idx)) != -1) {
    switch (opt) {
      case fixedcolor: {
        auto tmp = get_range();
        res.m_fixed = tmp >= 0;
        res.m_fixed_color = static_cast<uint8_t>(tmp);
      } break;
      case begin: {
        res.m_begin = get_range();
      } break;
      case end: {
        res.m_end = get_range();
      } break;
      case refreshrate: {
        res.m_refresh_rate = atoi(optarg);
      } break;
      case help: {
        print_help();
        exit(-1);
      } break;
    }
  }
  return res;
}
