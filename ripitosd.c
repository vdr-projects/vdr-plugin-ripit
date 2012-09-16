#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <vdr/osdbase.h>
#include <vdr/config.h>
#include "ripitosd.h"
#include "i18n.h"

const cFont *font;


cRipitOsd::cRipitOsd() :cOsdMenu("")
{
  font = cFont::GetFont(fontSml);
}

cRipitOsd::~cRipitOsd()
{
  DisplayMenu()->SetTitle(tr("AudioCD Ripper"));
  // keep
}

bool cRipitOsd::Rip_On(void)
{
  return access("/tmp/ripit.process",F_OK) == 0;
}


eOSState cRipitOsd::ProcessKey(eKeys Key)
{

     Display();

     
     eOSState state = cOsdMenu::ProcessKey(Key);
     if (state == osUnknown) {
    	switch (Key) {

          case kRed:
	  case kOk:
	        return osEnd;
		break;

          case kBlue:
	        if (!Rip_On()) {
		  Start_Encode();
		  Display();
	          }	
	        else {
	          Abort_Encode();
		  Display();
	        }	

	  default: break;
	}	
     } 
 return osContinue;
}


void cRipitOsd::Start_Encode(void)
{
  char *buffer;
  char godown[256], noquiet[256], eject[256], remote[256], ripopts[256], presetarg[256], crcarg[256];
  int lowbit = 0;
  int maxbit = 0;

  if(RipitSetup.Ripit_halt)     strcpy(godown ,"--halt");  else strcpy(godown,"");
  if(RipitSetup.Ripit_noquiet)  strcpy(noquiet,"");        else strcpy(godown,"--quiet");
  if(RipitSetup.Ripit_eject)    strcpy(eject  ,"--eject"); else strcpy(eject,"");
  
  if(!RipitSetup.Ripit_remote) strcpy(remote,"");
    else
      strcpy(remote,RipitSetup.Ripit_remotevalue);
  
  
  
  if(RipitSetup.Ripit_fastrip) {
    strcpy(ripopts, "-Z");
  }
  else {
    strcpy(ripopts, ""); 
  }

  if       (RipitSetup.Ripit_lowbitrate ==  0) lowbit =  32;
  else if  (RipitSetup.Ripit_lowbitrate ==  1) lowbit =  64;
  else if  (RipitSetup.Ripit_lowbitrate ==  2) lowbit =  96;
  else if  (RipitSetup.Ripit_lowbitrate ==  3) lowbit = 112;
  else if  (RipitSetup.Ripit_lowbitrate ==  4) lowbit = 128;
  else if  (RipitSetup.Ripit_lowbitrate ==  5) lowbit = 160;
  else if  (RipitSetup.Ripit_lowbitrate ==  6) lowbit = 192;
  else if  (RipitSetup.Ripit_lowbitrate ==  7) lowbit = 224;
  else if  (RipitSetup.Ripit_lowbitrate ==  8) lowbit = 256;
  else if  (RipitSetup.Ripit_lowbitrate ==  9) lowbit = 320;

  if       (RipitSetup.Ripit_maxbitrate ==  0) maxbit =  32;
  else if  (RipitSetup.Ripit_maxbitrate ==  1) maxbit =  64;
  else if  (RipitSetup.Ripit_maxbitrate ==  2) maxbit =  96;
  else if  (RipitSetup.Ripit_maxbitrate ==  3) maxbit = 112;
  else if  (RipitSetup.Ripit_maxbitrate ==  4) maxbit = 128;
  else if  (RipitSetup.Ripit_maxbitrate ==  5) maxbit = 160;
  else if  (RipitSetup.Ripit_maxbitrate ==  6) maxbit = 192;
  else if  (RipitSetup.Ripit_maxbitrate ==  7) maxbit = 224;
  else if  (RipitSetup.Ripit_maxbitrate ==  8) maxbit = 256;
  else if  (RipitSetup.Ripit_maxbitrate ==  9) maxbit = 320;

  if       (RipitSetup.Ripit_preset ==  0) strcpy(presetarg, "");
  else if  (RipitSetup.Ripit_preset ==  1) strcpy(presetarg, "--preset 64");
  else if  (RipitSetup.Ripit_preset ==  2) strcpy(presetarg, "--alt-preset 192");
  else if  (RipitSetup.Ripit_preset ==  3) strcpy(presetarg, "--preset extreme -V 2 --vbr-new -h");
  else if  (RipitSetup.Ripit_preset ==  4) strcpy(presetarg, "--preset 320 -h");


  if(RipitSetup.Ripit_crc) {
    strcpy(crcarg, "-p");
  }
  else {
    strcpy(crcarg, ""); 
  }

  asprintf(&buffer,"`echo 'Ripping process started....' > /tmp/ripit.log; touch /tmp/ripit.process; nice -n %i /usr/bin/ripit.pl %s %s %s %s --bitrate %i --maxrate %i --device %s --lameopt '%s %s %s' --ripopt '%s' --nointeraction --outputdir '%s'`&",
					RipitSetup.Ripit_nice,
					noquiet,
					eject,
					remote,
					godown,
					lowbit,
					maxbit,
					RipitSetup.Ripit_dev,
					presetarg,
					RipitSetup.Ripit_encopts,
					crcarg,
					ripopts,
					RipitSetup.Ripit_dir);

  dsyslog("Ripit: Executing '%s'",buffer);
  SystemExec(buffer);
	free(buffer);
	
}

void cRipitOsd::Abort_Encode(void)
{
  char *buffer;
  asprintf(&buffer, "killall ripit.pl ; killall lame ; killall cdparanoia ; echo 'PROCESS MANUALLY ABORTED' > /tmp/ripit.log; rm -f /tmp/ripit.process");   
  esyslog("Ripit: Executing '%s'\nProcess manually aborted ...!!!\n",buffer);
  SystemExec(buffer);
  free(buffer);

  Display();
//keep
}


void cRipitOsd::External_Start(const char *Device)
{
  char *buffer;
  char godown[256], noquiet[256], eject[256], remote[256], ripopts[256], presetarg[256], crcarg[256], device[64];
  int lowbit = 0;
  int maxbit = 0;
  
  if(Device)
    strcpy(device,Device);
  else
    strcpy(device,RipitSetup.Ripit_dev);
    


  if(RipitSetup.Ripit_halt)     strcpy(godown ,"--halt");  else strcpy(godown,"");
  if(RipitSetup.Ripit_noquiet)  strcpy(noquiet,"");        else strcpy(godown,"--quiet");
  if(RipitSetup.Ripit_eject)    strcpy(eject  ,"--eject"); else strcpy(eject,"");
  
  if(!RipitSetup.Ripit_remote) strcpy(remote,"");
    else
      strcpy(remote,RipitSetup.Ripit_remotevalue);
  
  
  
  if(RipitSetup.Ripit_fastrip) {
    strcpy(ripopts, "-Z");
  }
  else {
    strcpy(ripopts, ""); 
  }

  if       (RipitSetup.Ripit_lowbitrate ==  0) lowbit =  32;
  else if  (RipitSetup.Ripit_lowbitrate ==  1) lowbit =  64;
  else if  (RipitSetup.Ripit_lowbitrate ==  2) lowbit =  96;
  else if  (RipitSetup.Ripit_lowbitrate ==  3) lowbit = 112;
  else if  (RipitSetup.Ripit_lowbitrate ==  4) lowbit = 128;
  else if  (RipitSetup.Ripit_lowbitrate ==  5) lowbit = 160;
  else if  (RipitSetup.Ripit_lowbitrate ==  6) lowbit = 192;
  else if  (RipitSetup.Ripit_lowbitrate ==  7) lowbit = 224;
  else if  (RipitSetup.Ripit_lowbitrate ==  8) lowbit = 256;
  else if  (RipitSetup.Ripit_lowbitrate ==  9) lowbit = 320;

  if       (RipitSetup.Ripit_maxbitrate ==  0) maxbit =  32;
  else if  (RipitSetup.Ripit_maxbitrate ==  1) maxbit =  64;
  else if  (RipitSetup.Ripit_maxbitrate ==  2) maxbit =  96;
  else if  (RipitSetup.Ripit_maxbitrate ==  3) maxbit = 112;
  else if  (RipitSetup.Ripit_maxbitrate ==  4) maxbit = 128;
  else if  (RipitSetup.Ripit_maxbitrate ==  5) maxbit = 160;
  else if  (RipitSetup.Ripit_maxbitrate ==  6) maxbit = 192;
  else if  (RipitSetup.Ripit_maxbitrate ==  7) maxbit = 224;
  else if  (RipitSetup.Ripit_maxbitrate ==  8) maxbit = 256;
  else if  (RipitSetup.Ripit_maxbitrate ==  9) maxbit = 320;

  if       (RipitSetup.Ripit_preset ==  0) strcpy(presetarg, "");
  else if  (RipitSetup.Ripit_preset ==  1) strcpy(presetarg, "--preset 64");
  else if  (RipitSetup.Ripit_preset ==  2) strcpy(presetarg, "--alt-preset 192");
  else if  (RipitSetup.Ripit_preset ==  3) strcpy(presetarg, "--preset extreme -V 2 --vbr-new -h");
  else if  (RipitSetup.Ripit_preset ==  4) strcpy(presetarg, "--preset 320 -h");


  if(RipitSetup.Ripit_crc) {
    strcpy(crcarg, "-p");
  }
  else {
    strcpy(crcarg, ""); 
  }

  asprintf(&buffer,"`echo 'Ripping process started....' > /tmp/ripit.log; touch /tmp/ripit.process; nice -n %i /usr/bin/ripit.pl %s %s %s %s --bitrate %i --maxrate %i --device %s --lameopt '%s %s %s' --ripopt '%s' --nointeraction --outputdir '%s'`&",
					RipitSetup.Ripit_nice,
					noquiet,
					eject,
					remote,
					godown,
					lowbit,
					maxbit,
					device,
					presetarg,
					RipitSetup.Ripit_encopts,
					crcarg,
					ripopts,
					RipitSetup.Ripit_dir);

  dsyslog("Ripit: Executing '%s'",buffer);
  SystemExec(buffer);
	free(buffer);
	
}

void cRipitOsd::External_Abort(void)
{
  char *buffer;
  asprintf(&buffer, "killall ripit.pl ; killall lame ; killall cdparanoia ; echo 'PROCESS MANUALLY ABORTED' > /tmp/ripit.log; rm -f /tmp/ripit.process");   
  esyslog("Ripit: Executing '%s'\nProcess manually aborted ...!!!\n",buffer);
  SystemExec(buffer);
  free(buffer);
//keep
}


void cRipitOsd::Display(void)
{
  cOsdMenu::Display();

  using namespace std;
  ifstream logfile("/tmp/ripit.log");
  std::string line;
  std::string line1;
  std::string line2;
  std::string line3;
  std::string line4;
  std::string line5;
  std::string line6;
  std::string line7;
  std::string line8;
  std::string line9;
  std::string line10;
  std::string line11;
  std::string line12;
  std::string line13;
  std::string line14;
  std::string line15;
  std::string line16;
//  std::string line17;
//  std::string line18;
//  std::string line19;
//  std::string line20;
//  std::string line21;


  // check for running process  
  if (Rip_On()) {
    DisplayMenu()->SetTitle(tr("Process started..."));
    DisplayMenu()->SetText(tr("Ready To Rumble"), 0);
    SetHelp(tr("Parent"), NULL, NULL, tr("Abort"));
  }    
  else {
    DisplayMenu()->SetTitle(tr("No process started"));
    DisplayMenu()->SetText(tr("No process started"), 0);
    SetHelp(tr("Parent"), NULL, NULL, tr("Start"));
  }    
  
  // read last lines of logfile
  if(logfile.is_open()) {
    while(!logfile.eof()) {
      getline(logfile, line);
      line1  = line2;
      line2  = line3;
      line3  = line4;
      line4  = line5;
      line5  = line6;
      line6  = line7;
      line7  = line8;
      line8  = line9;
      line9  = line10;
      line10 = line11;
      line11 = line12;
      line12 = line13;
      line13 = line14;
      line14 = line15;
      line15 = line16;
//      line16 = line17;

      line16 = line;
//      line17 = line18;
//      line18 = line19;
//      line19 = line20;
//      line20 = line21;
//      line21 = line;
    }
    logfile.close();
  }    

  // display logfile  
  char *buffer;
  asprintf(&buffer, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", line1.c_str(),
													    line2.c_str(),
													    line3.c_str(),
													    line4.c_str(),
													    line5.c_str(),
                                                                                			    line6.c_str(),
													    line7.c_str(),
													    line8.c_str(),
													    line9.c_str(),
													    line10.c_str(),
													    line11.c_str(),
													    line12.c_str(),
													    line13.c_str(),
													    line14.c_str(),
													    line15.c_str(),
													    line16.c_str());
//													    line17.c_str();
//													    line18.c_str(),
//													    line19.c_str(),
//													    line20.c_str(),
//													    line21.c_str());
  DisplayMenu()->SetText(buffer, 0);
  free(buffer);
}
