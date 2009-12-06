#ifndef _GDENGINE_LIST_H_
#define _GDENGINE_LIST_H_

#include <GDEngine/Types.h>

typedef struct _GDList GDList;

typedef GDBool (*GDForeachFunc)   (GDUInt index,
                                   void *data, 
                                   void *userData);

typedef GDBool (*GDSearchCmpFunc) (void *data, 
                                   void *userData);

GDList *gdListAlloc    (void);
void    gdListRelease  (GDList *list, GDReleaseFunc releaseFunc);

void    gdListClear    (GDList *list, GDReleaseFunc releaseFunc);

GDUInt  gdListSize     (GDList *list);
GDBool  gdListAppend   (GDList *list, void *data);

void *  gdListAt       (GDList *list, GDUInt index);
GDBool  gdListContains (GDList *list, void *data);

void    gdListForeach  (GDList *list,
                        GDForeachFunc func,
                        void *userData);
void *  gdListSearch   (GDList *list,
                        GDSearchCmpFunc func,
                        void *userData);

void *  gdListTakeAt   (GDList *list, GDUInt index);

void    gdListRemove      (GDList *list, void *data);
void    gdListRemoveAt    (GDList *list, GDUInt index);
void    gdListRemoveLast  (GDList *list);
void    gdListRemoveFirst (GDList *list);

#endif /* !_GDENGINE_LIST_H_ */

