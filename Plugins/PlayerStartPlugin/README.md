# PlayerStartPlugin
The PlayerStartPlugin lets you easily setup, manage and activate different PlayerStart Actors in your Game via the WorldSettings from the Editor Outliner.

## Description 

1. PSWorldSettings
Module contains a custom AWorldSettings implementation with a "DefaultPlayerStartTag" which stores the selected PlayerStart from the Editor Outliner. Further this module also has a GlobalDefinitions.h file which implements a custom Log-Category for UE_LOG calls.

2. PlayerStartPlugin
This module contains all the Editor customization needed for selecting and using PlayerStarts.


## Installation and setup 
1. Download the Plugin from the Epic Marketplace
2. Enable Plugin in the UE4 Editor => Restart the Editor
3. Set PSWorldSettings as default WorldSettings class in Project-Settings > WorldSettings
4. Set PlayerStartGameModeBase as GameMode-Override in the WorldSettings or create your own GameMode with PlayerStartGameModeBase as a parent and use this class as GameMode Override.
5. Place PlayerStarts on the map
6. Remove the PlayerCharacters from the Map to activate the placed PlayerStarts as SpawnPoints
7. Set the current/preferred PlayerStart in the WorldSettings in the Editor Outliner
8. Start the Game and test the setup PlayerStart

