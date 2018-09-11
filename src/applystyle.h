#ifndef APPLYSTYLE_H
#define APPLYSTYLE_H

/**
 * The main apply style class.
 * It gets called from the plugin class after the options have been set in the dialog
 */

#include <QObject>
#include <QVector>

#include "plugins/scribusAPI/document.h"

namespace ScribusPlugin {
namespace ApplyStyle {

/**
 * @brief The main "Apply Style" class. It gets called by `ApplyStylePlugin` for showing the "Apply Style" dialog.
 */
class ApplyStyle
{
    public:
        ApplyStyle(ScribusAPI::Document &document)
        : document{document}
        {}
        ~ApplyStyle() {}
    private:
        ScribusAPI::Document &document;

};

} // namespaces
}

#endif // APPLYSTYLE_H
