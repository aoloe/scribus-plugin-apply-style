 /**
 * This is the entry point for the plugin.
 * All the methods defined here are called by Scribus' plugin execution code.
 */

#ifndef APPLYSTYLEPLUGIN_H
#define APPLYSTYLEPLUGIN_H

#include "pluginapi.h"
#include "scplugin.h"

class QString;
class ScribusDoc;
class ScribusMainWindow;

#include "ui/applystyledialog.h" // for ApplyStyleDialogListItem

/**
 * This is the standard entry point for the plugin and is automatically loaded by Scribus.
 * @brief Standard entry point for the plugin; Attaches itself to the menu, shows the "Settings" dialog and calls `ApplyStyle::doInsert()`
 */
class PLUGIN_API ApplyStylePlugin : public ScActionPlugin
{
	Q_OBJECT
public:

	// Standard plugin implementation
	ApplyStylePlugin();
	virtual ~ApplyStylePlugin();
	/*!
	\author Ale Rimoldi
	\brief Run the Apply Style
	\param filename a file to export to
	\retval bool true
	*/
	virtual bool run(ScribusDoc* doc=0, QString filename = QString::null);
	virtual const QString fullTrName() const;
	virtual const AboutData* getAboutData() const;
	virtual void deleteAboutData(const AboutData* about) const;
	virtual void languageChange();
	virtual void addToMainWindowMenu(ScribusMainWindow *) {};

private slots:
	void applyStyle(ApplyStyleDialogListItem style);
private:
    ScribusAPIDocument* scribusDocument;
};

extern "C" PLUGIN_API int applystyleplugin_getPluginAPIVersion();
extern "C" PLUGIN_API ScPlugin* applystyleplugin_getPlugin();
extern "C" PLUGIN_API void applystyleplugin_freePlugin(ScPlugin* plugin);

#endif // APPLYSTYLEPLUGIN_H
