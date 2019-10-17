 /**
 * This is the entry point for the plugin.
 * All the methods defined here are called by Scribus' plugin execution code.
 */

#ifndef APPLYSTYLEPLUGIN_H
#define APPLYSTYLEPLUGIN_H

#include "pluginapi.h"
#include "scplugin.h"

#include <QString>
#include <memory>

class ScribusDoc;
class ScribusMainWindow;

#include "ui/dialog.h" // for ApplyStyleDialogListItem

namespace API {
	class Document;
}

namespace ScribusPlugin {
namespace ApplyStyle {

/**
 * This is the standard entry point for the plugin and is automatically loaded by Scribus.
 * @brief Standard entry point for the plugin; Attaches itself to the menu, shows the "Settings" dialog and calls `ApplyStyle::doInsert()`
 */
class PLUGIN_API Plugin : public ScActionPlugin
{
	Q_OBJECT
public:

	// Standard plugin implementation
	Plugin();
	virtual ~Plugin();
	/*!
	\author Ale Rimoldi
	\brief Run the Apply Style
	\param filename a file to export to
	\retval bool true
	*/
	virtual bool run(ScribusDoc* doc, const QString& filename = QString::null) override;
	virtual const QString fullTrName() const override;
	virtual const AboutData* getAboutData() const override;
	virtual void deleteAboutData(const AboutData* about) const override;
	virtual void languageChange() override;
	virtual void addToMainWindowMenu(ScribusMainWindow *) override {};

private slots:
	void applyStyle(ListItem style);
private:
    std::shared_ptr<API::Document> document;
};

} // namespaces
}

extern "C" PLUGIN_API int applystyleplugin_getPluginAPIVersion();
extern "C" PLUGIN_API ScPlugin* applystyleplugin_getPlugin();
extern "C" PLUGIN_API void applystyleplugin_freePlugin(ScPlugin* plugin);

#endif // APPLYSTYLEPLUGIN_H
