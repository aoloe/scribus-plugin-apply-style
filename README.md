# Apply a style

Scribus plugin for applying a style through a small in-place dialog.

Press `cltr-shift-space` to trigger the "Apply a style" dialog:

![Apply paragraph styles](assets/apply-h1-list.gif | width=400)

Simply type the first letters of the style name and press the `Return` key.

You can also apply character styles:

![Apply character styles](assets/apply-code.gif | width=400)

Take care, that at the time of writing, you should first select some text before being able to apply any charcter formatting.

## Features

The dialog is composed by:
  - A text box for typing part of the styles name (spaces are ignored)
  - A list showing the matching styles:
    - the first style in alphabetical order is preselected.
    - the currently matching style is marked as bold.
    - paragraph styles are prefixed by a ¶, character styles by T.
  - `Tab` moves to the next style in the list
  - `Return` selects the first style in the list.
  - `Esc` closes the dialog without applying the style.
- No mouse interaction is possible (the policy will only be reivisde, if somebody can present a valid reason for using the mouse).

### Future plans

- Can be launched through a shortcut and the menues (for discovaribility).
- If scribus is in edit mode, the dialog shows at the cursor position. (The dialog is currently in the middle of the window)
- Otherwise, if a text frame is selected, shows at a yet to be defined position in the visible part of the text frame (or somewhere in the window)
- The list of matching styles should be empty if too many styles are matching.
- Preselect the last style applied?
- `Shift-Tab` should go backwards in the list.
- Show icons for each type of style.
- Support other types of styles as text styles.
- allow to apply the style to multiple items of the same type.

## Installing

First make sure that you have the ScribusAPI plugin installed (https://github.com/aoloe/scribus-plugin-API).

Clone the `scribus-plugin-export-plugin` repository and put – or symlink – its `src` directory into `scribus/plugins/` as `applystyle`. Then add 

    ADD_SUBDIRECTORY(applyStyle)

to `CMakeList.txt` file in `scribus/plugins/`.

`make` your Scribus.

In `File > Preferences > Keyboard Shortcuts` set `Ctrl-Shift-Space` for the `Apply a Style` command.

_Warning_: If you're compiler does not default to c++11, you will have to add `-DWANT_CPP11` to your cmake command.



## Todo

- get the cursor position on the screen
- refresh the rendering of the frame and mark the document as dirty.
- move the `ApplyStyleDialogListItem` struct away from the dialog file.
- Get "h1" to match "Heading 1" and "dp" "Default Paragraph Style" (space is the delimiter, if there is no direct match)

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
