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

| Menus                             | More Menus                              | Lots of Menus                               |
| --------------------------------- | --------------------------------------- | ------------------------------------------- |
| ![Main Menu][MainMenu]            | ![Edit Item Menu][EditItemMenu]         | ![Change Location Menu][ChangeLocationMenu] |
| ![Alter Text Menu][AlterTextMenu] | ![Edit Text Menu][EditTextMenu]         | ![Select Text Menu][SelectTextMenu]         |
| ![Settings Menu][SettingsMenu]    | ![Insert/Delete Menu][InsertDeleteMenu] |                                             |

(*Sorry for the poor image quality!*)

The `X` in the top right corner is the menu cursor. A long press on the button, or pressing the second button when the top `X` is shown, will close the menu screen, and from the **Main Menu**, the Name Badge screen will be shown again.

A short press on the button will move the menu cursor down, cycling through the menu options.

### Main Menu

![Main Menu][MainMenu]

The **Main Menu** is opened by a long press on the button, or a press of the second button. It provides the entry point for editing the current screen. To edit different screens, change screens before opening the menu. (By design, one screen is unable to be edited, so that suppliers can ensure that their custom screen is always available. The **Main Menu** is not able to be opened when that screen is shown.)

- **`Next`** and **`Prev`** change the current text item being edited.
- **`Edit Item`**, **`Alter Text`**, and **`Settings`** open the respective menus.

### Edit Item Menu

![Edit Item Menu][EditItemMenu]

From this menu, all the attributes of the current text item (selected from the **Main Menu**) are able to be changed.

- **`Change Location`** opens the **Change Location** menu to allow the item's position on screen to be changed.
- **`Change Font`** cycles through the four fonts.
- **`Change Size`** switches the double-sized text display on and off fo this item.
- **`Select Text`** opens the **Select Text** menu to change the portion of the complete text that is selected to be shown.
- **`Alter Text`** opens the **Alter Text** menu to allow the selected portion of text to be altered.

### Change Location Menu

![Change Location Menu][ChangeLocationMenu]

TODO

### Select Text Menu

![Select Text Menu][SelectTextMenu]

TODO

### Alter Text Menu

![Alter Text Menu][AlterTextMenu]

TODO

### Edit Text Menu

![Edit Text Menu][EditTextMenu]

TODO

### Insert/Delete Menu

![Insert/Delete Menu][InsertDeleteMenu]

TODO

### Settings Menu

![Settings Menu][SettingsMenu]

TODO

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
