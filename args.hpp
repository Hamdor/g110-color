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

#ifndef ARGS_HPP
#define ARGS_HPP

namespace g110 {

struct args {
  uint16_t m_vid;
  uint16_t m_pid;
  bool     m_fixed;
  uint8_t  m_fixed_color;
  uint8_t  m_begin;
  uint8_t  m_end;
  int      m_refresh_rate;
};

struct arg_parser {
  /**
   * Parse arguments from given cstring
   * @returns `args` with parsed arguments
   */
  static args parse_args(int argc, char* argv[]);

  /**
   * Print help message
   */
  static void print_help();
};

} // namespace g110

#endif // ARGS_HPP
