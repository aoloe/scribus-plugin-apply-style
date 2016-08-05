#ifndef APPLYSTYLESELECTION_H
#define APPLYSTYLESELECTION_H

/**
 * @brief Store the information about the current selection.
 */
class ApplyStyleSelection
{

public:
    ApplyStyleSelection() {};
    ~ApplyStyleSelection() {};

    bool textFrame;
    bool editMode;
    int x;
    int y;
};

#endif
