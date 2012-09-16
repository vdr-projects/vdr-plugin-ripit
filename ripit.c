/*
 * mcrip.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#include <vdr/interface.h>
#include "setup.h"
#include "ripit.h"
#include "i18n.h"

cPluginRipit::cPluginRipit(void)
{
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}

cPluginRipit::~cPluginRipit()
{
  // Clean up after yourself!
}


const char *cPluginRipit::CommandLineHelp(void)
{
  // Return a string that describes all known command line options.
  return NULL;
}

bool cPluginRipit::ProcessArgs(int argc, char *argv[])
{
  // Implement command line argument processing here if applicable.
  return true;
}

bool cPluginRipit::Initialize(void)
{
  // Initialize any background activities the plugin shall perform.
  return true;
} 


bool cPluginRipit::Start(void)
{
  // Start any background activities the plugin shall perform. 
  RegisterI18n(Phrases);
  return true;
}


void cPluginRipit::Housekeeping(void)
{
  // Perform any cleanup or other regular tasks.
}


const char *cPluginRipit::MainMenuEntry(void)
{
  return RipitSetup.Ripit_hidden ? 0 : tr(MAINMENUENTRY);
}

cOsdObject *cPluginRipit::MainMenuAction(void)
{
  return new cRipitOsd;
}  


#if APIVERSNUM >= 10331
const char **cPluginRipit::SVDRPHelpPages(void)
{
  static const char *HelpPages[] = {

    "START\n"
    "	'START [device]'  Start a new rip process. If 'device' is given , use this one else from setup",
    "ABORT\n"
    "	'ABORT'  Abort a running rip process",
    "STATUS\n"
    "	'STATUS' Shows status of ripit",
    NULL
    };
  return HelpPages;    
}

cString cPluginRipit::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  if(!strcasecmp(Command,"START")) {
    if(ripitosd->Rip_On()) {
      ReplyCode=550;
      return "Another rip process is running, Can't start new one";
      }
    else {
      if(*Option) {
        if(access(Option, F_OK)==0) {
          ripitosd->External_Start(Option);
          }
	else {
	  ReplyCode=550;
	  return "Device don't exist, Stopped";  
	  }
	}
      else
        ripitosd->External_Start(0);
        	
      return "New rip process started";
    }
  }
  else if(!strcasecmp(Command,"ABORT")) {
    if(!ripitosd->Rip_On()) {
      ReplyCode=550;
      return "Can't abort process because no one is running";
      }
    else {  
      ripitosd->External_Abort();
      return "Rip process aborted";
      }
    }
  else if(!strcasecmp(Command,"STATUS")) {
    if(ripitosd->Rip_On())
      return "A rip process is running";
    else
      return "No rip process is running";  
    }
  else {
    ReplyCode=502; return "Wrong command";
  }    
  return NULL;
}
#endif


cMenuSetupPage *cPluginRipit::SetupMenu(void)
{
  // Return a setup menu in case the plugin supports one.
  return new cMenuRipitSetup;
} 

bool cPluginRipit::SetupParse(const char *Name, const char *Value)
{
  // Parse your own setup parameters and store their values.
  if (!strcasecmp(Name, "Ripit_hidden"))              RipitSetup.Ripit_hidden     = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_halt"))           RipitSetup.Ripit_halt       = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_noquiet"))        RipitSetup.Ripit_noquiet    = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_eject"))          RipitSetup.Ripit_eject      = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_fastrip"))        RipitSetup.Ripit_fastrip    = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_lowbitrate"))     RipitSetup.Ripit_lowbitrate = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_maxbitrate"))     RipitSetup.Ripit_maxbitrate = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_preset"))         RipitSetup.Ripit_preset     = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_crc"))            RipitSetup.Ripit_crc        = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_encopts"))        strn0cpy(RipitSetup.Ripit_encopts, Value, sizeof(RipitSetup.Ripit_encopts));
  else if (!strcasecmp(Name, "Ripit_dev"))            strn0cpy(RipitSetup.Ripit_dev, Value, sizeof(RipitSetup.Ripit_dev));
  else if (!strcasecmp(Name, "Ripit_dir"))            strn0cpy(RipitSetup.Ripit_dir, Value, sizeof(RipitSetup.Ripit_dir));
  else if (!strcasecmp(Name, "Ripit_nice"))           RipitSetup.Ripit_nice       = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_remote"))         RipitSetup.Ripit_remote     = atoi(Value);
  else if (!strcasecmp(Name, "Ripit_remotevalue"))    strn0cpy(RipitSetup.Ripit_remotevalue, Value, sizeof(RipitSetup.Ripit_remotevalue));

  else return false;
    return true;
}

cMenuRipitSetup::cMenuRipitSetup(void)
{

  Setup();
/*  static const char allowed[] = { "abcdefghijklmnopqrstuvwxyz0123456789-_/" };
  int current = Current();

  Clear();

  Add(new cMenuEditBoolItem( tr("Shutdown after finished"),       &RipitSetup.Ripit_halt));
  Add(new cMenuEditBoolItem( tr("Verbose output"),                &RipitSetup.Ripit_noquiet));
  Add(new cMenuEditBoolItem( tr("Eject after finished"),          &RipitSetup.Ripit_eject));
  Add(new cMenuEditBoolItem( tr("Fast mode"),                      &RipitSetup.Ripit_fastrip));

  lowbitrate[0] =  "32";
  lowbitrate[1] =  "64";
  lowbitrate[2] =  "96";
  lowbitrate[3] = "112";
  lowbitrate[4] = "128";
  lowbitrate[5] = "160";
  lowbitrate[6] = "192";
  lowbitrate[7] = "224";
  lowbitrate[8] = "256";
  lowbitrate[9] = "320";
  Add(new cMenuEditStraItem( tr("Min. bitrate"),                         &RipitSetup.Ripit_lowbitrate, 10, lowbitrate));

  maxbitrate[0] =  "32";
  maxbitrate[1] =  "64";
  maxbitrate[2] =  "96";
  maxbitrate[3] = "112";
  maxbitrate[4] = "128";
  maxbitrate[5] = "160";
  maxbitrate[6] = "192";
  maxbitrate[7] = "224";
  maxbitrate[8] = "256";
  maxbitrate[9] = "320";
  Add(new cMenuEditStraItem( tr("Max. bitrate"),                         &RipitSetup.Ripit_maxbitrate, 10, maxbitrate));

  preset[0] = tr("none");
  preset[1] = tr("low");
  preset[2] = tr("standard");
  preset[3] = tr("great");
  preset[4] = tr("best");
  Add(new cMenuEditStraItem( tr("Presets"),                         &RipitSetup.Ripit_preset, 5, preset));

  Add(new cMenuEditBoolItem( tr("CRC-check"),                             &RipitSetup.Ripit_crc));
  Add(new cMenuEditStrItem( tr("More encoder settings"),            RipitSetup.Ripit_encopts, 255, allowed));
  Add(new cMenuEditStrItem( tr("Device"),                           RipitSetup.Ripit_dev, 255, allowed));
  Add(new cMenuEditStrItem( tr("Directory for ripped tracks"),      RipitSetup.Ripit_dir, 255, allowed));
  Add(new cMenuEditIntItem( tr("Priority of task (nice)"),         &RipitSetup.Ripit_nice, -20, 19));

  Add(new cMenuEditBoolItem( tr("Encode remotely"),                &RipitSetup.Ripit_remote));
  if(RipitSetup.Ripit_remote)
    Add(new cMenuEditStrItem( tr("Options for remote encoding"),    RipitSetup.Ripit_remotevalue, 255, allowed));

  SetCurrent(Get(current));
  Display();
*/
} 

void cMenuRipitSetup::Setup(void)
{
  static const char allowed[] = { "abcdefghijklmnopqrstuvwxyz0123456789-_/" };
  int current = Current();

  Clear();

  Add(new cMenuEditBoolItem( tr("Hide mainmenu entry"),		  &RipitSetup.Ripit_hidden));
  Add(new cMenuEditBoolItem( tr("Shutdown after finished"),       &RipitSetup.Ripit_halt));
  Add(new cMenuEditBoolItem( tr("Verbose output"),                &RipitSetup.Ripit_noquiet));
  Add(new cMenuEditBoolItem( tr("Eject after finished"),          &RipitSetup.Ripit_eject));
  Add(new cMenuEditBoolItem( tr("Fast mode"),                     &RipitSetup.Ripit_fastrip));

  lowbitrate[0] =  "32";
  lowbitrate[1] =  "64";
  lowbitrate[2] =  "96";
  lowbitrate[3] = "112";
  lowbitrate[4] = "128";
  lowbitrate[5] = "160";
  lowbitrate[6] = "192";
  lowbitrate[7] = "224";
  lowbitrate[8] = "256";
  lowbitrate[9] = "320";
  Add(new cMenuEditStraItem( tr("Min. bitrate"),                         &RipitSetup.Ripit_lowbitrate, 10, lowbitrate));

  maxbitrate[0] =  "32";
  maxbitrate[1] =  "64";
  maxbitrate[2] =  "96";
  maxbitrate[3] = "112";
  maxbitrate[4] = "128";
  maxbitrate[5] = "160";
  maxbitrate[6] = "192";
  maxbitrate[7] = "224";
  maxbitrate[8] = "256";
  maxbitrate[9] = "320";
  Add(new cMenuEditStraItem( tr("Max. bitrate"),                         &RipitSetup.Ripit_maxbitrate, 10, maxbitrate));

  preset[0] = tr("none");
  preset[1] = tr("low");
  preset[2] = tr("standard");
  preset[3] = tr("great");
  preset[4] = tr("best");
  Add(new cMenuEditStraItem( tr("Presets"),                         &RipitSetup.Ripit_preset, 5, preset));

  Add(new cMenuEditBoolItem( tr("CRC-check"),                             &RipitSetup.Ripit_crc));
  Add(new cMenuEditStrItem( tr("More encoder settings"),            RipitSetup.Ripit_encopts, 255, allowed));
  Add(new cMenuEditStrItem( tr("Device"),                           RipitSetup.Ripit_dev, 255, allowed));
  Add(new cMenuEditStrItem( tr("Directory for ripped tracks"),      RipitSetup.Ripit_dir, 255, allowed));
  Add(new cMenuEditIntItem( tr("Priority of task (nice)"),         &RipitSetup.Ripit_nice, -20, 19));

  Add(new cMenuEditBoolItem( tr("Encode remotely"),                &RipitSetup.Ripit_remote));
  if(RipitSetup.Ripit_remote)
    Add(new cMenuEditStrItem( tr("Options for remote encoding"),    RipitSetup.Ripit_remotevalue, 255, allowed));

  SetCurrent(Get(current));
  Display();

}


void cMenuRipitSetup::Store(void)
{
  SetupStore("Ripit_hidden",        RipitSetup.Ripit_hidden);
  SetupStore("Ripit_halt",          RipitSetup.Ripit_halt);
  SetupStore("Ripit_noquiet",       RipitSetup.Ripit_noquiet);
  SetupStore("Ripit_eject",         RipitSetup.Ripit_eject);
  SetupStore("Ripit_fastrip",       RipitSetup.Ripit_fastrip);
  SetupStore("Ripit_lowbitrate",    RipitSetup.Ripit_lowbitrate);
  SetupStore("Ripit_maxbitrate",    RipitSetup.Ripit_maxbitrate);
  SetupStore("Ripit_crc",           RipitSetup.Ripit_crc);
  SetupStore("Ripit_preset",        RipitSetup.Ripit_preset);
  SetupStore("Ripit_encopts",       RipitSetup.Ripit_encopts);
  SetupStore("Ripit_dev",           RipitSetup.Ripit_dev);
  SetupStore("Ripit_dir",           RipitSetup.Ripit_dir);
  SetupStore("Ripit_nice",          RipitSetup.Ripit_nice);
  SetupStore("Ripit_remote",        RipitSetup.Ripit_remote);
  SetupStore("Ripit_remotevalue",   RipitSetup.Ripit_remotevalue);
} 


eOSState cMenuRipitSetup::ProcessKey(eKeys Key)
{
  int oldvalue = RipitSetup.Ripit_remote;
  
  eOSState state = cMenuSetupPage::ProcessKey(Key);

  if( (Key != kNone) && (RipitSetup.Ripit_remote != oldvalue) ) {
    Setup();
  }
      
  return state;
}      



VDRPLUGINCREATOR(cPluginRipit); // Don't touch this!
