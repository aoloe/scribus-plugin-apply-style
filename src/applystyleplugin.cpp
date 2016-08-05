#include "applystyle.h"
#include "applystyleplugin.h"

#include "scribuscore.h"
#include "scribusdoc.h"

#include <QDebug>

#include "module/applystyleselection.h"
#include "ui/applystyledialog.h"

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
 * If a document is open, show the export dialog and call `ApplyStyle::doExport()`.
 *
 * @todo:
 * - do not show the dialog if Scribus runs in "server" mode.
 */
bool ApplyStylePlugin::run(ScribusDoc* doc, QString target)
{

	Q_ASSERT(target.isNull());
	ScribusDoc* currDoc=doc;
	if (currDoc == 0)
		currDoc = ScCore->primaryMainWindow()->doc;
	if (currDoc == 0)
		return false;

    qDebug() << "apply a style";
	ApplyStyle *applystyle = new ApplyStyle();

	applystyle->setScribusDocument(currDoc);
    ApplyStyleSelection selection = applystyle->getSelection();
    if (selection.textFrame)
    {
        // ApplyStyleDialog *dialog = new ApplyStyleDialog(currDoc->scMW(), currDoc, "dlg", true, 0);
        ApplyStyleDialog *dialog = new ApplyStyleDialog(currDoc->scMW());
    }
    // TODO:
    // - get the list of styles
    // - get the cursor position on the screen
    // - show the dialog and let the user choose a style
    // - apply the style
    // EpubExportDialog *dialog = new EpubExportDialog(currDoc->scMW());
	// applystyle->setOptions(options);
    bool success = true;
	// bool success = applystyle->doAppend();
	delete applystyle;
	return success;
}
