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
4. Restart Project / UE4 Editor (Important!)
5. Set PlayerStartGameModeBase as GameMode-Override in the WorldSettings or create your own GameMode with PlayerStartGameModeBase as a parent and use this class as GameMode Override in WorldSettings.
6. Place PlayerStarts on the map
7. Remove the own PlayerCharacter from the Map to activate the placed PlayerStarts as SpawnPoints
8. Set the current/preferred PlayerStart in the WorldSettings in the Editor Outliner
9. Start the Game and test the setup PlayerStart

### Setup without removing Player Character from Map
If you don't want to remove your Player Character (previous step #7) from the map you can setup the plugin with the following procedure:

5. Create a child class (Blueprint) of PlayerStartGameModeBase and set this class as GameMode Override in the WorldSettings in your maps Editor Outliner.
5a. Set your Player Character as Default Pawn Class in the Selected Game Mode Details > This way you can keep your Player Character on the map and use the functionality of the PlayerStartPlugin as well

## Version History
### 1.0.6 (6) - 17.08.2022
- Bugfix to avoid crashing when adding PlayerStarts after switching levels. Added PendingDelete(). Thanks to "scheltopusik" for reporting this bug

### 1.0.5 (5) - 08.05.2022
- Initial released version
