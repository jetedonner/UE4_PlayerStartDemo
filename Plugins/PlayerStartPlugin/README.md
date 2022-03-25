# PlayerStartPlugin
The PlayerStartPlugin lets you easily setup, manage and activate different PlayerStart Actors in your Game via the WorldSettings from the Editor Outliner.

## Description 

1. PSWorldSettings
Module contains a custom AWorldSettings implementation with a "DefaultPlayerStartTag" which stores the selected PlayerStart from the Editor Outliner. Further this module also has a GlobalDefinitions.h file which implements a custom Log-Category for UE_LOG calls.

2. PlayerStartPlugin
This module contains all the Editor customization needed for selecting and using PlayerStarts.


## Installation and setup 
1. Download Plugin from the Epic Marketplace
2. Enable Plugin in the UE4 Editor => Restart the Editor
3. Set PSWorldSettings as default in Project-Settings > WorldSettings
4. Place PlayerStarts on the map
5. Set the current / prefered PlayerStart in the WorldSettings in the Editor Outliner
6. Start the Game and test the setup PlayerStart


## Implementation 

## Credits
- [Start icons created by Freepik - Flaticon](https://www.flaticon.com/free-icons/start)
