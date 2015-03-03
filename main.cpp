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

#include <iostream>

#include "args.hpp"
#include "controller.hpp"

using std::cerr;
using std::cout;
using std::endl;
using namespace g110;

int main(int argc, char* argv[]) {
  auto opts = arg_parser::parse_args(argc, argv);
  controller c(std::move(opts));
  if (!c.valid()) {
    cerr << "Error init controller, try with super-user." << endl;
    return -1;
  }
  c.run();
  return 0;
}
