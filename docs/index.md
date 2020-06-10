# Datacute Name Badge

![DatacuteNameBadge][DatacuteNameBadge]

## Features

Four editable screens.

- 128 x 64 pixels.
- Customisable by the user, after installation on the device.
- Customisations stored in EEPROM

Eight lines of text are possible.

- Though two lines of large text are perfect for showing your name, with multiple screens available users can set up their device to have one screen showing personal contact details, and another screen showing business contact details.

Four fonts are available.

- A small 6 x 8 pixel font.
- A larger 8 x 16 pixel font.
- A graphical icon font is available.
  - Shading, line drawing, and icons, some of which are used by the device's menu.
- A fourth font is designed to be altered by the supplier of the device, used to display their QR Code or small graphical logo.

Two text sizes are possible.

- In addition to the two different sized text fonts, each item of text can be shown double-sized. The larger text font shown double-sized takes up half the height of the display.

Each screen can have up to 16 different texts shown on it.

- That may seem excessive, till you wish to show:
  - A border along the top, (1)
  - A portion of a border on each side of each of six rows, (12)
  - A border along the bottom, (1)
  - Two items of text. (2)
- Each item of text displayed is a selection from a long string of text, (limited to 256 ascii characters), so the same portion of text can be selected and displayed on multiple screens, without having to re-enter the text, making the initial set-up by the user easier.

One non-editable screen.

- The supplier/programmer of the device can design a screen with a QR Code or small logo, which is unable to be altered by the user.

On-device editing is possible using only a single button.

- Two-button operation is also supported.

Adjustable brightness.

Battery voltage shown (only shown within the settings menu).

The ATTiny85 MCU will power off in-between button presses to save power.

## Operation

The device supports being operated with either one or two buttons. A short press (less than 1/2 second) of the first button navigates between screens and menu options. A long press (over 1/2 second) of the first button, or a press of the second button, opens the menu system, or activates the selected menu option.

When the device is first turned on, the **Settings** menu is shown, allowing the user to initialise the device.

## Menus

The menu system may seem quite extensive. The reason is that in order to support single-button operation, there needs to be a lot of menu options.

|                                   |                                             |                                         |
| --------------------------------- | ------------------------------------------- | --------------------------------------- |
| ![Main Menu][MainMenu]            | ![Select Text Menu][SelectTextMenu]         | ![Settings Menu][SettingsMenu]          |
| ![Edit Item Menu][EditItemMenu]   | ![Change Location Menu][ChangeLocationMenu] |                                         |
| ![Alter Text Menu][AlterTextMenu] | ![Edit Text Menu][EditTextMenu]             | ![Insert/Delete Menu][InsertDeleteMenu] |

(*Sorry for the poor image quality!*)

The `X` in the top right corner is the menu cursor. A long press on the button, or pressing the second button when the top `X` is shown, will close the menu screen, and from the **Main Menu**, the Name Badge screen will be shown again.

A short press on the button will move the menu cursor down, cycling through the menu options.

### Main Menu

![Main Menu][MainMenu]

The **Main Menu** is opened by a long press on the button, or a press of the second button. It provides the entry point for editing the current screen. To edit different screens, change screens before opening the menu. (By design, one screen is unable to be edited, so that suppliers can ensure that their custom screen is always available. The **Main Menu** is not able to be opened when that screen is shown.)

- **`Next`** and **`Prev`** change the current text item being edited.
- **`Select Text`**, **`Edit Item`**, and **`Settings`** open the respective menus.

### Select Text Menu

![Select Text Menu][SelectTextMenu]

Text items on screen show a short selection from a longer text made up of all the items' texts joined together. This makes it easy to show your name on several screens, by re-selecting the same portion for another item.

Items cannot be edited until they have a selection of text to edit, so for new items, the first **Main Menu** option to use is to **`Select Text`**, and in this menu the first menu option to use is to make the text selection **`Longer`**, then move the selection **`Right`** or **`Left`** to an unused portion of the text.

When editing the items, it is possible to **`Insert`** and **`Delete`**, however those actions are fairly slow due to needing to rewrite large portions of the EEPROM. It is better to start with a selection that is longer than you need, then come back to the text selection menu and make it **`Shorter`** once you know how long it needs to be.

If 250 or so characters of text will be more than enough for you, then leaving some space between items' selections will make it easier to change things later.

### Edit Item Menu

![Edit Item Menu][EditItemMenu]

From the **Edit Item Menu**, all the attributes of the current text item (selected from the **Main Menu**) are able to be changed.

- **`Change Location`** opens the **Change Location Menu** to allow the item's position on screen to be changed.
- **`Change Font`** cycles through the four fonts.
- **`Change Size`** switches the double-sized text display on and off fo this item.
- **`Select Text`** opens the **Select Text Menu** to change the portion of the complete text that is selected to be shown.
- **`Alter Text`** opens the **Alter Text Menu** to allow the selected portion of text to be altered.

### Change Location Menu

![Change Location Menu][ChangeLocationMenu]

The location of the text item on the screen can be changed in multiples of 8 pixels.

- **`Left`**, **`Right`**, **`Up`**, and **`Down`** move the text item, and the text is briefly shown in the new location.

### Alter Text Menu

![Alter Text Menu][AlterTextMenu]

The **Alter Text Menu**, and the menus opened from here, show the text being edited at the bottom of the screen, with an arrow pointing at the current letter being edited.

- **`Left`** and **`Right`** move the arrow to edit different letters in the text.
- **`Edit`** opens the **Edit Text Menu** to allow the letter to be changed.
- **`Insert/Delete`** opens the **Insert/Delete Menu** to allow insertion and deletion of letters.

### Edit Text Menu

![Edit Text Menu][EditTextMenu]

The **Edit Text Menu** allows the letters of the text to be changed.

- **`Left`** and **`Right`** move the arrow to edit different letters in the text.
- **`Next Letter`** cycles through the alphabet, numbers, and symbols. Only characters that are contained in the currently selected font are available. The font may map the displayed 7-bit ascii character to an image, for example, the arrows in the icon font will be shown on this screen as the characters 6,7,8 and 9.
- **`Prev Letter`** cycles through in the opposite direction.

#### Icon Font Mapping

| Editing | Displayed | Editing | Displayed   |
| :-----: | :-------: | :-----: | :---------: |
|  space  |  space    |    0    | X           |
|    !    |    ░      |    1    | Tick        |
|    "    |    ▒      |    2    | Circle      |
|    #    |    ▓      |    3    | +           |
|    $    |    █      |    4    | -           |
|    %    |    │      |    5    | ...         |
|    &    |    ─      |    6    | Left Arrow  |
|    '    |    ┼      |    7    | Right Arrow |
|    (    |    ┐      |    8    | Down Arrow  |
|    )    |    └      |    9    | Up Arrow    |
|    *    |    ┘      |    :    | Heart       |
|    +    |    ┌      |
|    ,    |    ┤      |
|    -    |    ┴      |
|    .    |    ┬      |
|    /    |    ├      |

*The supplier of the device may have altered or augmented this font.*

### Insert/Delete Menu

![Insert/Delete Menu][InsertDeleteMenu]

The **Insert/Delete Menu** allows for insertion and deletion of characters from the item text.

Since each item's text is selected from the long string of the text for all the items joined together, when an insertion or deletion occurs, large portions of the EEPROM need to be rewritten.

- **`Left`** and **`Right`** move the arrow to edit different letters in the text.
- **`Insert`** and **`Delete`** perform the respective modifications.

### Settings Menu

![Settings Menu][SettingsMenu]

The **Settings Menu** is displayed on first use, when the EEPROM in the device has not been initialised. At that time, **`Reset All?`** needs to be selected to initialise the device so that it is able to display the Name Badge screens and store user customisations.

- **`Brighter`** and **`Dimmer`** increase and decrease the display's brightness. The brightness value *wraps around* rather than stopping at the limits. The various hardware options for SSD1306 OLED screens respond in different amounts to brightness settings, so the change in brightness may seem very small. The power usage and battery life is directly proportional to the brightness. If the device is showing a QR Code, then a dimmer display is recommended. Smart-phones have difficulty reading QR codes from bright displays.
- **`Reset All?`** **removes all user customisations**, and re-initialises the device, re-writing the EEPROM contents with the default Name Badge screens.

The current battery voltage is displayed on the **Settings Menu**. When the battery voltage gets too low, the EEPROM may become corrupted, with occasional random letters or symbols appearing in place of the expected text.

## User Customisation - On-Device

TODO

## Supplier Customisation - Source Code Alteration

TODO

[DatacuteNameBadge]: images/DatacuteNameBadge.png "Datacute Name Badge"
[MainMenu]: images/MenuMain.png "Main Menu"
[EditItemMenu]: images/MenuEditItem.png "Edit Item Menu"
[ChangeLocationMenu]: images/MenuChangeLocation.png "Change Location Menu"
[EditTextMenu]: images/MenuEditText.png "Edit Text Menu"
[InsertDeleteMenu]: images/MenuInsertDelete.png "Insert/Delete Menu"
[SelectTextMenu]: images/MenuSelectText.png "Select Text Menu"
[AlterTextMenu]: images/MenuAlterText.png "Alter Text Menu"
[SettingsMenu]: images/MenuSettings.png "Settings Menu"
