#include <QDebug>

#include "applystyle.h"
#include "scribusdoc.h"

#include "module/applystyleselection.h"

#include "plugins/scribusAPI/scribusAPI.h"
#include "plugins/scribusAPI/scribusAPIDocument.h"
#include "plugins/scribusAPI/scribusAPIDocumentItem.h"
#include "plugins/scribusAPI/scribusAPIDocumentItemText.h"
// #include "plugins/scribusAPI/scribusAPIDocumentItemTextFormatting.h"

ApplyStyle::ApplyStyle()
{
}

ApplyStyle::~ApplyStyle()
{
}

ApplyStyleSelection ApplyStyle::getSelection()
{
    ScribusAPIDocument* scribusDocument = new ScribusAPIDocument(this->scribusDoc);

	ScribusAPIDocumentItem* tocFrame = scribusDocument->getCurrentItem();

    ApplyStyleSelection selection;
	selection.textFrame = tocFrame &&  tocFrame->isTextFrame();
    if (!selection.textFrame)
        return selection;
    // bool editMode;
    return selection;
}
