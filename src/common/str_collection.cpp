#define Uses_TStreamableClass
#include "str_collection.hpp"

#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

const char * const _NEAR TStrCollection::name = "TStrCollection";

TStreamableClass RStrCollection( TStrCollection::name,
                                 TStrCollection::build,
                                 __DELTA(TStrCollection)
                               );

TStrCollection::TStrCollection( short aLimit, short aDelta ) noexcept :
    TCollection(aLimit, aDelta)
{
}

void TStrCollection::freeItem( void* item )
{
    delete[] (char *) item;
}

TStreamable *TStrCollection::build()
{
    return new TStrCollection( streamableInit );
}

void TStrCollection::writeItem( void *obj, opstream& os )
{
    os.writeString( (const char *)obj );
}

void *TStrCollection::readItem( ipstream& is )
{
    return is.readString();
}
