/*
 * AudioRipper plugin to VDR
 *
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

#include <string.h>

#include "setup.h"

cRipitSetup RipitSetup;

// --- cRipitSetup ---------------------------------------------------------------

cRipitSetup::cRipitSetup(void)
{
  Ripit_hidden = 0;
  Ripit_halt = 0;
  Ripit_noquiet = 0;
  Ripit_eject = 1;
  Ripit_fastrip = 0;
  Ripit_lowbitrate = 6;
  Ripit_maxbitrate = 9;
  Ripit_crc = 0;
  Ripit_preset = 2;
  strcpy(Ripit_encopts, "");
  strcpy(Ripit_dev,"/dev/cdrom");
  strcpy(Ripit_dir,"/vdr_daten/mp3/RippedCDs/tmp");
  Ripit_remote = 0;
  strcpy(Ripit_remotevalue,"--sshlist master,bedroom --scp");
  Ripit_nice = 5;
}
