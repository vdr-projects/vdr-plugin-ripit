/*
 * (C) 2005
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#ifndef ___SETUP_H
#define ___SETUP_H

// ----------------------------------------------------------------

class cRipitSetup {
public:
  cRipitSetup(void);
  int  Ripit_hidden;
  int  Ripit_halt;
  int  Ripit_noquiet;
  int  Ripit_eject;
  int  Ripit_fastrip;
  int  Ripit_lowbitrate;
  int  Ripit_maxbitrate;
  int  Ripit_crc;
  int  Ripit_preset;
  char Ripit_encopts[256];
  char Ripit_dev[256];
  char Ripit_dir[256];
  int  Ripit_remote;
  char Ripit_remotevalue[256];
  int  Ripit_nice;
  };

extern cRipitSetup RipitSetup;

#endif //___SETUP_H

