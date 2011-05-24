#include "IncludeFile.h"
#include "CDataSource.h"
#include "CMobileNode.h"
#include "CHomeAgent.h"
#include "CForeignAgent.h"

void help() {
  cout << "This binary could be use to start Data Source (DS), "
    "Home Agent (HA), Foreign Agent (FA), Mobile Node (MN)\n"
    "**Todo: Add functionality for node discovery and node validations**" << endl;
  cout << "1. DS HAIP HAPort " << endl;
  cout << "   Data Source requires Home Agent IP (HAIP) and Home Agent Port (HAPort)" << endl;
  cout << "2. HA listenPort FA1IP FA1Port FA2IP FA2Port" << endl;
  cout << "   Home Agent requires " << endl;
  cout << "    listenPort port to listen" << endl;
  cout << "    FA1IP, FA1Port : IP and port of foreign agent 1" << endl;
  cout << "    FA2IP, FA2Port : IP and port of foreign agent 2" << endl;
  cout << "3. FA listenPort MNIP MNPort" << endl;
  cout << "   Foreign Agent requires  " << endl;
  cout << "    listenPort port to listen" << endl;
  cout << "    MNIP, MNPort : IP and port of Mobile Node (MN)" << endl;
  cout << "4.MN listenPort HAIP HAPort" << endl;
  cout << "   Mobile Node requires  " << endl;
  cout << "    listenPort port to listen" << endl;
  cout << "    HAIP, HAPort : IP and port of Home Agent (HA)" << endl;
}

int main(int argc, char **argv) {

  // arg1 = send / recv
  // recv port#
  // send host port#
  try {
    if (argc < 3) {
      help();
      return -1;
    }

    if (strcmp(argv[1], "ds") == 0) {
      const char* szHAIP = argv[2];
      int nPort = atoi(argv[3]);

      CDataSource oDS(szHAIP, nPort);
      oDS.startSending();

    } else if (strcmp(argv[1], "ha") == 0) {
      if (argc < 7) {
        help();
        return -1;
      }

      int nListenPort = atoi(argv[2]);
      const char* szFA1IP = argv[3];
      int nFA1Port = atoi(argv[4]);
      const char* szFA2IP = argv[5];
      int nFA2Port = atoi(argv[6]);

      CHomeAgent oHA(nListenPort);
      oHA.addForeignAgent(0, szFA1IP, nFA1Port);
      oHA.addForeignAgent(1, szFA2IP, nFA2Port);
      oHA.listenNForward();
    } else if (strcmp(argv[1], "fa") == 0) {
      if (argc < 5) {
        help();
        return -1;
      }

      int nListenPort = atoi(argv[2]);
      const char* szMNIP = argv[3];
      int nMNPort = atoi(argv[4]);

      CForeignAgent oFA(nListenPort, szMNIP, nMNPort);
      oFA.startlistening();

    } else if (strcmp(argv[1], "mn") == 0) {
      if (argc < 5) {
        help();
        return -1;
      }

      int nListenPort = atoi(argv[2]);
      const char* szHA1IP = argv[3];
      int nHA1Port = atoi(argv[4]);

      CMobileNode oMN(nListenPort, szHA1IP, nHA1Port);
      oMN.startlistening();
    }
  } catch (const char *s) {
    cerr << "Exception occured" << s << endl;
  }
  return 0;
}
