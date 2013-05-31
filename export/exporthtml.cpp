#include "exporthtml.h"

ExportHTML::ExportHTML()
{

}


QString	ExportHTML::header() const
{
    return "<html>"
           "<head>"
            "</head>"
            "<body>";
}

QString	ExportHTML::footer() const
{
    return "</body>"
            "</html>";
}

QString	ExportHTML::exportNote(const Note& n, unsigned int level) const
{
    return "";
}
