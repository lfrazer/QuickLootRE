# Note from lfrazer

I am leaving this here as a partially completed port to VR for educational and development use of the community.  It is not working yet, but probably could work with a little love and care.  

# QuickLootRE

This project uses [JSON for Modern C++](https://github.com/nlohmann/json)

## Settings
Setting | Description
--- | ---
`disableInCombat` | Disables the loot menu from displaying in combat.
`disableTheft` | Disables the loot menu from displaying when thieving from containers.
`disablePickpocketing` | Disables the loot menu from displaying when pickpocketing.
`disableIfEmpty` | Disables the loot menu from displaying when empty.
`disableSingleLoot` | Disables single loot mode.
`disableForAnimals` | Disables the loot menu from displaying when looting animals.
`playAnimations` | Enables animations to play when opening/closing containers. This feature is experimental and best left off.
`itemLimit` | The maximum number of items to display in the loot menu at a given time.
`scale` | The scale of the loot menu GUI. A negative value will use the default of `25`.
`positionX` | The X position of the loot menu GUI. A negative value will use the default of `384`.
`positionY` | The Y position of the loot menu GUI. A negative value will use the default of `0`.
`opacity` | The opacity of the loot menu GUI. A negative value will use the default of `100`.
`singleLootModifier` | Determines the key used for the single loot feature. Valid inputs are: `"activate"`, `"readyWeapon"`, `"togglePOV"`, `"jump"`, `"sprint"`, `"sneak"`, `"shout"`, and `"toggleRun"`.
`takeMethod` | Determines the key used for the take feature. Valid inputs are: `"activate"`, `"readyWeapon"`, `"togglePOV"`, `"jump"`, `"sprint"`, `"sneak"`, `"shout"`, and `"toggleRun"`.
`takeAllMethod` | Determines the key used for the take all feature. Valid inputs are: `"activate"`, `"readyWeapon"`, `"togglePOV"`, `"jump"`, `"sprint"`, `"sneak"`, `"shout"`, and `"toggleRun"`.
`searchMethod` | Determines the key used for the search feature. Valid inputs are: `"activate"`, `"readyWeapon"`, `"togglePOV"`, `"jump"`, `"sprint"`, `"sneak"`, `"shout"`, and `"toggleRun"`.
`interfaceStyle` | Determines the interface style to use. Valid inputs are: `"default"`, and `"dialogue"`.
`sortOrder` | Defines the order items are sorted in the loot menu. Valid inputs are: `"name"`, `"count"`, `"value"`, `"weight"`, `"type"`, `"stolen"`, `"read"`, `"enchanted"`, `"pickPocketChance"`, and `"valuePerWeight"`. `sortOrder` is an array, so multiple inputs are acceptable.
