#include <QDebug>

#include "applystyle.h"
#include "scribusdoc.h"

#include "module/applystyleselection.h"

#include "plugins/scribusAPI/scribusAPIDocument.h"
#include "plugins/scribusAPI/scribusAPIDocumentItem.h"
#include "plugins/scribusAPI/scribusAPIDocumentItemText.h"
// #include "plugins/scribusAPI/scribusAPIDocumentItemTextFormatting.h"

ApplyStyleSelection* ApplyStyle::getSelection()
{
	ScribusAPIDocumentItem* tocFrame = document->getCurrentItem();

    ApplyStyleSelection* selection = new ApplyStyleSelection();
	selection->textFrame = tocFrame &&  tocFrame->isTextFrame();
    if (!selection->textFrame)
        return selection;
    // bool editMode;
    return selection;
}
