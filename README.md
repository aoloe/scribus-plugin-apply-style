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

- get the cursor position on the screen
- refresh the rendering of the frame and mark the document as dirty.
- apply also the character styles.
- move the `ApplyStyleDialogListItem` struct away from the dialog file.
- Get "h1" to match "Heading 1" and "dp" "Default Paragraph Style" (space is the delimiter)

Further ideas:

- Add an API function to know the position of the cursor in the frame (not the index, the x, y coordinates)
- Create a dialog that captures the keys but has not input field (if possible).
- Create a dialog that resizes according to the content (upwards or downwards)

## Notes

- avox says: "if you know the character position, you can use class TextLayout to find the relative position in the frame"
- the code around line 1882 in `pageitem_textframe.cpp` could also be interesting
- fuzzy autocomplete: <https://github.com/FuzzyAutocomplete/FuzzyAutocompletePlugin>
  - https://packagecontrol.io/packages/AutocompletionFuzzy
  - http://www.tomsquest.com/blog/2011/05/better-autocompletes-with-fuzzy-matching/
  - https://en.wikipedia.org/wiki/Approximate_string_matching
  - https://github.com/tomsquest/better-autocompletes-with-fuzzy-matching
  - http://www.dustindiaz.com/autocomplete-fuzzy-matching
- Maybe create a general runner:
  - Only a label, no lineedit
  - No mouse support (we might have a second one mouse based)
  - Multi stage fast actions (run, rotate, step (1, 10, 15, ...), ← →); with hints on what is available.
  - Placed at "standard" places (home, end, page up, page down for edges and center (  (home when already at home moves to the center); next launch at the precedent place.
