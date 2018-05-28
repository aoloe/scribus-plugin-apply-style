#include "applystyle.h"
#include "applystyleplugin.h"

#include "scribuscore.h"
#include "scribusdoc.h"

#include <QString>

#include <iostream>

#include "ui/applystyledialog.h"

#include "plugins/scribusAPI/scribus.h"
#include "plugins/scribusAPI/document.h"
#include "plugins/scribusAPI/textFrame.h"

int applystyleplugin_getPluginAPIVersion()
{
	return PLUGIN_API_VERSION;
}

ScPlugin* applystyleplugin_getPlugin()
{
	ApplyStylePlugin* plug = new ApplyStylePlugin();
	Q_CHECK_PTR(plug);
	return plug;
}

void applystyleplugin_freePlugin(ScPlugin* plugin)
{
	ApplyStylePlugin* plug = dynamic_cast<ApplyStylePlugin*>(plugin);
	Q_ASSERT(plug);
	delete plug;
}

ApplyStylePlugin::ApplyStylePlugin() : ScActionPlugin()
{
	// Set action info in languageChange, so we only have to do
	// it in one place.
	languageChange();
}

ApplyStylePlugin::~ApplyStylePlugin()
{
	// unregisterAll();
};

void ApplyStylePlugin::languageChange()
{
	// Note that we leave the unused members unset. They'll be initialised
	// with their default ctors during construction.
	// Action name
	m_actionInfo.name = "ApplyStyle";
	// Action text for menu, including accel
	m_actionInfo.text = tr("Apply a &Style");
	// Menu
    // TODO: move it to edit (does not seem to appear)
	// m_actionInfo.menu = "Edit";
	m_actionInfo.menu = "Insert";
	m_actionInfo.enabledOnStartup = false;
	m_actionInfo.needsNumObjects = -1;
}

const QString ApplyStylePlugin::fullTrName() const
{
	return QObject::tr("Apply Style");
}

const ScActionPlugin::AboutData* ApplyStylePlugin::getAboutData() const
{
	AboutData* about = new AboutData;
	about->authors = "Ale Rimoldi <a.l.e@ideale.ch>";
	about->shortDescription = tr("Let the user apply a style");
	about->description = tr("Apply a style");
	about->license = "MIT";
	Q_CHECK_PTR(about);
	return about;
}

void ApplyStylePlugin::deleteAboutData(const AboutData* about) const
{
	Q_ASSERT(about);
	delete about;
}

/**
 * This method is automatically called by Scribus when the plugin action is activated.
 *
 * If a document is open, check if a text frame is selected, call the style picker and apply the chosen style.
 */
bool ApplyStylePlugin::run(ScribusDoc* doc, QString target)
{

    // TODO: one day we will have to find out and document what target is good for...
    Q_ASSERT(target.isNull());


    // TODO: why is doc passed to the plugin and when it is set (what is its value?)
    document = ScribusAPI::Scribus::getActiveDocument(doc);
    if (!document.isOpen()) {
        return false;
    }

	auto applyStyle = ApplyStyle::ApplyStyle(document);

    // TODO: add getActiveTextItem() ?
    auto optionalDocumentItem = document.getActiveItem();
    if (!optionalDocumentItem.has_value()) {
        return false;
    }

    auto documentItem = optionalDocumentItem.value();

    if (!documentItem.isTextFrame()) {
        return false;
    }

    // TODO: convert the ApplyStyleDialog to use namespaces and non pointers.
    ApplyStyleDialog* dialog = new ApplyStyleDialog{doc->scMW(), document};
    connect(dialog, &ApplyStyleDialog::accepted, [this, dialog]() {
          this->applyStyle(dialog->getStyle());
    });
    dialog->setModal(true);
    dialog->show();

    bool success = true;
	return success;
}

void ApplyStylePlugin::applyStyle(ApplyStyleDialogListItem style)
{
    // TODO: do everything in run() or to share the selection
    // between run() and applyStyle()
    std::cout << style.name << std::endl;
    std::cout << style.type << std::endl;

    auto frame = document.getActiveItem();
	if (frame &&  frame->isTextFrame()) {
        if (style.type == "paragraph") {
            frame->getTextFrame().applyParagraphStyle(style.name);
        } else if (style.type == "character") {
            frame->getTextFrame().applyCharacterStyle(style.name);
        }
    }
}
