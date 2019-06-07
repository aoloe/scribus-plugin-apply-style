#include "plugin.h"

#include "scribuscore.h"
#include "scribusdoc.h"

#include <QString>

#include "ui/dialog.h"

#include "plugins/scribusAPI/scribus.h"
#include "plugins/scribusAPI/document.h"
#include "plugins/scribusAPI/textFrame.h"

int applystyleplugin_getPluginAPIVersion()
{
	return PLUGIN_API_VERSION;
}

ScPlugin* applystyleplugin_getPlugin()
{
	auto plug = new ScribusPlugin::ApplyStyle::Plugin();
	Q_CHECK_PTR(plug);
	return plug;
}

void applystyleplugin_freePlugin(ScPlugin* plugin)
{
	auto plug = dynamic_cast<ScribusPlugin::ApplyStyle::Plugin*>(plugin);
	Q_ASSERT(plug);
	delete plug;
}

namespace ScribusPlugin {
namespace ApplyStyle {

Plugin::Plugin() : ScActionPlugin()
{
	// Set action info in languageChange, so we only have to do
	// it in one place.
	languageChange();
}

Plugin::~Plugin()
{
	// unregisterAll();
};

void Plugin::languageChange()
{
	m_actionInfo.name = "ApplyStyle";
	// Action text for menu, including accel
	m_actionInfo.text = tr("Apply a &Style");
	// Menu
    // TODO: move it to edit (does not seem to appear)
	// m_actionInfo.menu = "Edit";
	m_actionInfo.menu = "Insert";
	m_actionInfo.keySequence = "Ctrl+ ";
	m_actionInfo.enabledOnStartup = false;
	m_actionInfo.needsNumObjects = -1;
}

const QString Plugin::fullTrName() const
{
	return QObject::tr("Apply Style");
}

const ScActionPlugin::AboutData* Plugin::getAboutData() const
{
	AboutData* about = new AboutData;
	about->authors = "Ale Rimoldi <a.l.e@ideale.ch>";
	about->shortDescription = tr("Let the user apply a style");
	about->description = tr("Apply a style");
	about->license = "MIT";
	Q_CHECK_PTR(about);
	return about;
}

void Plugin::deleteAboutData(const AboutData* about) const
{
	Q_ASSERT(about);
	delete about;
}

/**
 * This method is automatically called by Scribus when the plugin action is activated.
 *
 * If a document is open, check if a text frame is selected, call the style picker and apply the chosen style.
 */
bool Plugin::run(ScribusDoc* doc, const QString& target)
{

    // TODO: one day we will have to find out and document what target is good for...
    Q_ASSERT(target.isNull());


    // TODO: why is doc passed to the plugin and when is it set (what is its value?)
    // TODO: rename ScribusAPI to ScribusPlugin::API
    document = API::Scribus::getActiveDocument(doc);
    if (!document.isOpen()) {
        return false;
    }

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
    auto dialog = new Dialog{doc->scMW(), document};
    connect(dialog, &Dialog::accepted, [this, dialog]() {
          this->applyStyle(dialog->getStyle());
    });
    dialog->setModal(true);
    dialog->show();

    bool success = true;
	return success;
}

void Plugin::applyStyle(ListItem style)
{
    auto frame = document.getActiveItem();
	if (frame &&  frame->isTextFrame()) {
        if (style.type == "paragraph") {
            frame->getTextFrame().applyParagraphStyle(style.name);
        } else if (style.type == "character") {
            frame->getTextFrame().applyCharacterStyle(style.name);
        }
    }
}

} // namespaces
}
