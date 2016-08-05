/**
 * The main apply style class.
 * It gets called from the plugin class after the options have been set in the dialog
 */
#ifndef APPLYSTYLE_H
#define APPLYSTYLE_H

#include <QObject>
#include <QVector>

class ScribusDoc;
class ApplyStyleSelection;

/**
 * @brief The main apply style class. It gets called by `ApplyStylePlugin` after the the export dialog.
 */
class ApplyStyle : public QObject
{
    Q_OBJECT

public:
	ApplyStyle();
	~ApplyStyle();

    void setScribusDocument(ScribusDoc* scribusDoc) { this->scribusDoc = scribusDoc; }

    ApplyStyleSelection getSelection();
private:
    ScribusDoc* scribusDoc;

};

#endif // APPLYSTYLE_H
