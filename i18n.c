/*
 * i18n.c: Internationalization
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: i18n.c 1.3 2002/06/23 13:05:59 kls Exp $
 */

#include "i18n.h"

const tI18nPhrase Phrases[] = {
  { "RipIt",
    "AudioCD Ripper",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Extracteur CD",// En Francais Patrice Staudt 14.11.2006
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "AudioCD Ripper",
    "AudioCD Ripper",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Extracteur CD",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Start",
    "Starten",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Depart",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Abort",
    "Abbrechen",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Interrompre",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Parent",
    "Zur�ck",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Retour",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Process started...",
    "Vorgang gestartet",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "D�marrer la transformation",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Ready To Rumble",
    "Ready To Rumble",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Pr�ts pour la transformation",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "No process started",
    "Kein Vorgang gestartet",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Pas de travaux en cours",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "AudioCD Ripper",
    "AudioCD Ripper",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Extracteur CD",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Device",
    "Laufwerk",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Lecteur",
    "",// TODO
    "Asema laitehallinnassa",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Shutdown after finished",
    "Herunterfahren wenn fertig",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "�teindre lorsque c'est finit",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Verbose output",
    "Detailierte Anzeige",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Affichage d�tail�",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Eject after finished",
    "CD auswerfen wenn fertig",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Ejecter le CD lorsque l'extraction est finit",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Min. bitrate",
    "Min. Bitrate",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Bitrate min.",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Max. bitrate",
    "Max. Bitrate",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Bitrate max.",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Fast mode",
    "Schnelles Rippen",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Extraction rapide",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Presets",
    "Voreinstellung",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Pr�difinition",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "none",
    "Kein",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Pas de",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "low",
    "Niedrig",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Faible",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "standard",
    "Standard",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Standart",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "great",
    "Sehr gut",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Tr�s bonne",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "best",
    "Beste",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Exc�lente",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "CRC-check",
    "CRC-check",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "CRC-check",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "More encoder settings",
    "Mehr Encoder Optionen",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Plus d'option pour l'encodeur",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Directory for ripped tracks",
    "Speicherort f�r gerippte CD",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Fichiers pour les CD extraits",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Priority of task (nice)",
    "Priorit�t von Vorgang (nice)",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Priorit�e de la proc�dure (nice)",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Encode remotely",
    "Entferntes Encodieren",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Encodage sur un autre ordinateur",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Options for remote encoding",
    "Parameter f�r entferntes Encodieren",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Param�tre pour l'encodage � distance",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { "Hide mainmenu entry",
    "Hauptmen�eintrag verbergen",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "Invisible dans le menu principale",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
  },
  { NULL }
  };
