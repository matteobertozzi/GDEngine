#ifndef _GDENGINE_MODEL_READER_H_
#define _GDENGINE_MODEL_READER_H_

#include <GDEngine/Model.h>
#include <GDEngine/List.h>

typedef struct {
    GDList *models;
} GDModelReader;

GDBool gdModelReaderInit            (GDModelReader *reader);
void   gdModelReaderRelease         (GDModelReader *reader);

GDBool gdModelReaderRead (GDModelReader *reader, const char *filename);

GDBool gdModelReaderAddModel        (GDModelReader *reader,
                                     GDModel *model);

#endif /* !_GDENGINE_MODEL_READER_H_ */

