#include "modelreader.h"

GDBool __gdReadModelGdt (GDModelReader *reader, const char *filename);

GDBool gdModelReaderInit (GDModelReader *reader) {
    if (!(reader->models = gdListAlloc()))
        return(GD_FALSE);
    return(GD_TRUE);
}

void gdModelReaderRelease (GDModelReader *reader) {
    gdListRelease(reader->models, (GDReleaseFunc)gdModelRelease);
    reader->models = NULL;
}

GDBool gdModelReaderRead (GDModelReader *reader, const char *filename) {
    return(__gdReadModelGdt(reader, filename));
}

GDBool gdModelReaderAddModel (GDModelReader *reader, GDModel *model) {
    gdListAppend(reader->models, model);
    return(GD_TRUE);
}

