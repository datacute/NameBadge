/*
 * Simple Menu System
 */

typedef void (*ActionFunc) (void);
typedef void (*DisplayFunc) (void);

struct MenuItem {
  PGM_P name;
  const ActionFunc actionFn;
};

struct Menu {
  const DisplayFunc displayFn;
  const uint8_t exitMode;
  const uint8_t numItems;
  const MenuItem * items;
};

const char ITEM_NAME[] PROGMEM = { "Item" };
const char NEXT_NAME[] PROGMEM = { "Next" };
const char PREV_NAME[] PROGMEM = { "Prev" };
const char SELECT_TEXT_NAME[] PROGMEM = { "Select Text" };
const char EDIT_ITEM_NAME[] PROGMEM = { "Edit Item" };
const char SETTINGS_NAME[] PROGMEM = { "Settings" };

const char CHANGE_LOCATION_NAME[] PROGMEM = { "Change Location" };
const char CHANGE_FONT_NAME[] PROGMEM = { "Change Font" };
const char CHANGE_SIZE_NAME[] PROGMEM = { "Change Size" };
const char ALTER_TEXT_NAME[] PROGMEM = { "Alter Text" };

const char LEFT_NAME[] PROGMEM = { "Left" };
const char RIGHT_NAME[] PROGMEM = { "Right" };
const char UP_NAME[] PROGMEM = { "Up" };
const char DOWN_NAME[] PROGMEM = { "Down" };

const char LONGER_NAME[] PROGMEM = { "Longer" };
const char SHORTER_NAME[] PROGMEM = { "Shorter" };

const char EDIT_NAME[] PROGMEM = { "Edit" };
const char INSERT_DELETE_NAME[] PROGMEM = { "Insert/Delete" };

const char NEXT_LETTER_NAME[] PROGMEM = { "Next Letter" };
const char PREV_LETTER_NAME[] PROGMEM = { "Prev Letter" };

const char INSERT_NAME[] PROGMEM = { "Insert" };
const char DELETE_NAME[] PROGMEM = { "Delete" };

const char INCREASE_CONTRAST_NAME[] PROGMEM = { "Brighter" };
const char DECREASE_CONTRAST_NAME[] PROGMEM = { "Dimmer" };
const char RESET_EEPROM_NAME[] PROGMEM = { "Reset All?" };

/*

0. Display Screen

*/

#define DRAW_SCREEN_MODE 0
void drawScreen(void);

/*
1. Item Selection

<<Back to 0. Display Screen>> Item 1 - Datacute
Next
Prev
Edit Item
Alter Text
Settings
*/

#define ITEM_SELECTION_MODE 1
void drawItemMenu(void);
void nextItemAction(void);
void prevItemAction(void);
void selectTextAction(void);
void editItemAction(void);
void settingsAction(void);

const MenuItem itemSelectionMenuItems[5] PROGMEM = {
// name              action fn
  {NEXT_NAME,        nextItemAction   },
  {PREV_NAME,        prevItemAction   },
  {SELECT_TEXT_NAME, selectTextAction },
  {EDIT_ITEM_NAME,   editItemAction   },
  {SETTINGS_NAME,    settingsAction   }
};

/*
2. Edit Item Options

<<Back to 1. Item Selection>> Item 1 - Datacute
Change Location
Change Font
Change Size
Select Text
Alter Text

*/

#define EDIT_ITEM_MODE 2
void changeLocationAction(void);
void changeFontAction(void);
void changeSizeAction(void);
void alterTextAction(void);

const MenuItem editItemMenuItems[5] PROGMEM = {
// name                  action fn
  {CHANGE_LOCATION_NAME, changeLocationAction },
  {CHANGE_FONT_NAME,     changeFontAction     },
  {CHANGE_SIZE_NAME,     changeSizeAction     },
  {SELECT_TEXT_NAME,     selectTextAction     },
  {ALTER_TEXT_NAME,      alterTextAction      }
};

/*
3. Change Location

<<Back to 2. Edit Item Options>> Item 1 - 0,0
Left
Right
Up
Down

*/

#define CHANGE_LOCATION_MODE 3
void locationLeftAction(void);
void locationRightAction(void);
void locationUpAction(void);
void locationDownAction(void);

const MenuItem changeLocationMenuItems[4] PROGMEM = {
// name        action fn
  {LEFT_NAME,  locationLeftAction  },
  {RIGHT_NAME, locationRightAction },
  {UP_NAME,    locationUpAction    },
  {DOWN_NAME,  locationDownAction  }
};

/*
4. Select Text

<<Back to 2. Edit Item Options>> Item 1 - Datacute
Left
Right
Longer
Shorter
Alter Text

*/

#define SELECT_TEXT_MODE 4
void drawSelectTextMenu(void);
void selectTextLeftAction(void);
void selectTextRightAction(void);
void selectTextLongerAction(void);
void selectTextShorterAction(void);

const MenuItem selectTextMenuItems[4] PROGMEM = {
// name             action fn
  {LEFT_NAME,       selectTextLeftAction    },
  {RIGHT_NAME,      selectTextRightAction   },
  {LONGER_NAME,     selectTextLongerAction  },
  {SHORTER_NAME,    selectTextShorterAction }
};

/*
5. Text Edit Options

<<Back to 2. Edit Item Options>> Item 1 - Datacute
Left
Right
Edit
Insert/Delete

*/

#define TEXT_EDIT_OPTIONS_MODE 5
void drawTextEditOptionsMenu(void);
void textEditLeftAction(void);
void textEditRightAction(void);
void textEditAction(void);
void textEditInsertDeleteAction(void);

const MenuItem textEditOptionsMenuItems[4] PROGMEM = {
// name                action fn
  {LEFT_NAME,          textEditLeftAction         },
  {RIGHT_NAME,         textEditRightAction        },
  {EDIT_NAME,          textEditAction             },
  {INSERT_DELETE_NAME, textEditInsertDeleteAction }
};

/*
6. Text Edit

<<Back to 5. Text Edit Options>> Item 1 - Datacute
Next Letter
Prev Letter
Change Case

*/

#define TEXT_EDIT_MODE 6
void textEditNextAction(void);
void textEditPrevAction(void);

const MenuItem textEditMenuItems[4] PROGMEM = {
// name              action fn
  {LEFT_NAME,        textEditLeftAction  },
  {RIGHT_NAME,       textEditRightAction },
  {NEXT_LETTER_NAME, textEditNextAction  },
  {PREV_LETTER_NAME, textEditPrevAction  }
};

/*
7. Text Insert and Delete

<<Back to 5. Text Edit Options>> Item 1 - Datacute
Left
Right
Insert     (All items that start after get shifted. All items that start before and end on or after get lengthened)
Delete     (All items that start after get shifted. All items that start before and end on or after get shortened)

*/

#define TEXT_INSERT_DELETE_MODE 7
void drawTextInsertDeleteMenu(void);
void textInsertAction(void);
void textDeleteAction(void);

const MenuItem textInsertDeleteMenuItems[4] PROGMEM = {
// name         action fn
  {LEFT_NAME,   textEditLeftAction  },
  {RIGHT_NAME,  textEditRightAction },
  {INSERT_NAME, textInsertAction    },
  {DELETE_NAME, textDeleteAction    }
};

/*
8. Settings

<<Back to 0. Display Screen>> Settings       3.2V
Increase Contrast
Decrease Contrast
Reset EEPROM
 
 */
#define SETTINGS_MENU_MODE 8
void drawSettingsMenu(void);
void settingsIncreaseContractAction(void);
void settingsDecreaseContractAction(void);
void settingsResetAction(void);

static const MenuItem settingsMenuItems[3] PROGMEM = {
// name                    action fn
  {INCREASE_CONTRAST_NAME, settingsIncreaseContractAction },
  {DECREASE_CONTRAST_NAME, settingsDecreaseContractAction },
  {RESET_EEPROM_NAME,      settingsResetAction            }
};

/*
 * Menu Interactions
 */

const Menu menus[9] PROGMEM = {
// displayFn                 exit #  items
  {drawScreen,               1,   0, NULL                      },
  {drawItemMenu,             0,   5, itemSelectionMenuItems    },
  {drawItemMenu,             1,   5, editItemMenuItems         },
  {drawItemMenu,             2,   4, changeLocationMenuItems   },
  {drawSelectTextMenu,       2,   4, selectTextMenuItems       },
  {drawTextEditOptionsMenu,  2,   4, textEditOptionsMenuItems  },
  {drawTextEditOptionsMenu,  5,   4, textEditMenuItems         },
  {drawTextInsertDeleteMenu, 5,   4, textInsertDeleteMenuItems },
  {drawSettingsMenu,         0,   3, settingsMenuItems         },
};
