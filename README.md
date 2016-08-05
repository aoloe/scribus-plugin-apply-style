# Apply a style

Scribus plugin for applying a style through a small in-place dialog.

## Features

### Planned

- can only be launched through the menues (for discovaribility) and a shortcut.
- if scribus is in edit mode, the dialog shows at the cursor position
- otherwise, if a text frame is selected, shows at a yet to be defined position in the visible part of the text frame (or somewhere in the window)
- the dialog is composed by:
  - a text box (probably static) for typing a part of the styles name (spaces are ignored)
  - a list showing the matching styles
    - none before the first character has been typed
    - define a maximum of styles to be shown
    - a prefix number for selecting a style
    - return selects the first style in the list
    - ESC closes the dialog without applying the style
- no mouse interaction is possible (except if somebody can present a valid use case for using the mouse)
- show icons for each type of style.
- Support other types of styles as text styles.
- allow to apply the style to multiple items of the same type.

## Todo

- Add an API function to know the position of the cursor in the frame (not the index, the x, y coordinates)
- Create a dialog that captures the keys but has not input field (if possible).
- Create a dialog that resizes according to the content (upwards or downwards)

## Notes

- avox says: "if you know the character position, you can use class TextLayout to find the relative position in the frame"
- the code around line 1882 in `pageitem_textframe.cpp` could also be interesting
