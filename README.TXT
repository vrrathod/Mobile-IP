This project tries to implement primitive level of mobile IP simulation. 
Scenario:
It uses a constant time source generating simple event to be transmitted to mobile node. This source is in home network, hence it is always connected to home agent. The mobile node may switch backn and forth to foreign agent 1 and 2. Home agent gets notifications from Mobile node about current foreign agent. When Home agent receives source generated event it forwards it to the appropriate foreign agent and eventually to mobile node.

General arguments

  1. simulator DS HAIP HAPort  
     Data Source requires Home Agent IP (HAIP) and Home Agent Port (HAPort) 

  2. simulator HA listenPort FA1IP FA1Port FA2IP FA2Port 
     Home Agent requires  
      listenPort port to listen 
      FA1IP, FA1Port : IP and port of foreign agent 1 
      FA2IP, FA2Port : IP and port of foreign agent 2 

  3. simulator FA listenPort MNIP MNPort 
     Foreign Agent requires   
      listenPort port to listen 
      MNIP, MNPort : IP and port of Mobile Node (MN) 

  4. simulator MN listenPort HAIP HAPort 
     Mobile Node requires   
      listenPort port to listen 
      HAIP, HAPort : IP and port of Home Agent (HA) 

Todo: Add functionality for node discovery and node validations.

