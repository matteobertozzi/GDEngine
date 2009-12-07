/*
 * Copyright (c) 2009, Matteo Bertozzi <theo.bertozzi@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Matteo Bertozzi nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Matteo Bertozzi ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Matteo Bertozzi BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

