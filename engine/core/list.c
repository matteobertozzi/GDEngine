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

#include "alloc.h"
#include "list.h"

struct _GDNode {
    void *data;
    struct _GDNode *prev;
    struct _GDNode *next;
};

struct _GDList {
    struct _GDNode *cachePointer;
    GDUInt cacheIndex;

    struct _GDNode *last;
    struct _GDNode *first;
    GDUInt size;
};

static struct _GDNode *__list_find_node (GDList *list, void *data) {
    struct _GDNode *p;

    for (p = list->first; p != NULL; p = p->next) {
        if (p->data == data)
            return(p);
    }

    return(NULL);
}

static struct _GDNode *__list_node_at (GDList *list, GDUInt index) {
    struct _GDNode *p;
    GDUInt i;

    if (index == 0)
        return(list->first);

    if (index == (list->size - 1))
        return(list->last);

    /* Try to use Cache to speed-up movements */
    if (list->cachePointer != NULL) {
        GDUInt deltaAbs;
        GDInt delta;

        if ((delta = (list->cacheIndex - index)) == 0)
            return(list->cachePointer);

        deltaAbs = ((delta < 0) ? -delta : delta);
        if (deltaAbs < index && deltaAbs < (list->size - index)) {
            if (delta < 0) {
                while (deltaAbs-- > 0)
                    list->cachePointer = list->cachePointer->next;
            } else {
                while (deltaAbs-- > 0)
                    list->cachePointer = list->cachePointer->prev;
            }

            list->cacheIndex = index;
            return(list->cachePointer);
        }
    }

    /* Scan All List From the most convenient part */
    if (index < (list->size >> 1)) {
        for (i = 0, p = list->first; p != NULL; p = p->next, ++i) {
            if (i == index) {
                list->cachePointer = p;
                list->cacheIndex = index;
                return(p);
            }
        }
    } else {
        for (i = (list->size-1), p = list->last; p != NULL; p = p->prev, --i) {
            if (i == index) {
                list->cachePointer = p;
                list->cacheIndex = index;
                return(p);
            }
        }
    }

    return(NULL);
}

static void __list_free_node (GDList *list, struct _GDNode *node) {
    gdFree(node);
    list->size--;
    list->cacheIndex = 0;
    list->cachePointer = NULL;
}

GDList *gdListAlloc (void) {
    GDList *list;

    if ((list = gdAlloc(GDList)) == NULL)
        return(NULL);

    list->cachePointer = NULL;
    list->cacheIndex = 0;
    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return(list);
}

void gdListRelease (GDList *list, GDReleaseFunc releaseFunc) {
    if (list != NULL) {
        gdListClear(list, releaseFunc);
        gdFree(list);
    }
}

void gdListClear (GDList *list, GDReleaseFunc releaseFunc) {
    if (list != NULL) {
        struct _GDNode *node;

        list->cachePointer = NULL;
        while (list->first != NULL) {
            if ((node = list->first->next) != NULL)
                node->prev = NULL;

            /* Update Last Item If Necessary */
            if (list->first == list->last)
                list->last = node;

            /* Release First Item */
            if (releaseFunc != NULL)
                releaseFunc(list->first->data);
            gdFree(list->first);

            /* Set New First Node */
            list->first = node;
            list->size--;
        }
    }
}

GDUInt gdListSize (GDList *list) {
    if (list == NULL) return(0);
    return(list->size);
}

GDBool gdListAppend (GDList *list, void *data) {
    struct _GDNode *node;

    if ((node = gdAlloc(struct _GDNode)) == NULL)
        return(GD_FALSE);

    node->next = NULL;
    node->data = data;

    if (list->last != NULL)
        list->last->next = node;
    node->prev = list->last;
    list->last = node;

    if (list->first == NULL)
        list->first = node;

    list->size++;

    return(GD_TRUE);
}

void *gdListAt (GDList *list, GDUInt index) {
    struct _GDNode *node;

    if ((node = __list_node_at(list, index)) != NULL)
        return(node->data);

    return(NULL);
}

GDBool gdListContains (GDList *list, void *data) {
    return(__list_find_node(list, data) != NULL);
}

void gdListForeach (GDList *list, GDForeachFunc func, void *userData) {
    struct _GDNode *p;
    GDUInt i;

    for (i = 0, p = list->first; p != NULL; p = p->next, ++i) {
        if (func(i, p->data, userData))
            break;
    }
}

void *gdListSearch (GDList *list, GDSearchCmpFunc cmpFunc, void *userData) {
    struct _GDNode *p;

    for (p = list->first; p != NULL; p = p->next) {
        if (cmpFunc(p->data, userData))
            return(p->data);
    }

    return(NULL);
}

void *gdListTakeAt (GDList *list, GDUInt index) {
    void *data;

    if ((data = gdListAt(list, index)) == NULL)
        return(NULL);

    gdListRemoveAt(list, index);
    return(data);
}

void gdListRemove (GDList *list, void *data) {
    struct _GDNode *node;

    if ((node = __list_find_node(list, data)) != NULL) {
        if (node == list->first) {
            gdListRemoveFirst(list);
        } else if (node == list->last) {
            gdListRemoveLast(list);
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            __list_free_node(list, node);
        }
    }
}


void gdListRemoveAt (GDList *list, GDUInt index) {
    struct _GDNode *node;

    if (index == 0) {
        gdListRemoveFirst(list);
    } else if (index >= list->size) {
        gdListRemoveLast(list);
    } else if ((node = __list_node_at(list, index))) {
       node->prev->next = node->next;
       node->next->prev = node->prev;
       __list_free_node(list, node);
    }
}

void gdListRemoveLast (GDList *list) {
    if (list->last != NULL) {
        struct _GDNode *node;

        if ((node = list->last->prev) != NULL)
            node->next = NULL;

        if (list->last == list->first)
            list->first = node;

        __list_free_node(list, list->last);
        list->last = node;
    }
}

void gdListRemoveFirst (GDList *list) {
    if (list->first != NULL) {
        struct _GDNode *node;

        if ((node = list->first->next) != NULL)
            node->prev = NULL;

        if (list->first == list->last)
            list->last = node;

        __list_free_node(list, list->first);
        list->first = node;        
    }
}

