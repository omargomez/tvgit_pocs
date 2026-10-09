#pragma once

#define Uses_TCollection
#define Uses_ipstream
#define Uses_opstream
#define Uses_TStreamable
#include <tvision/tv.h>

// TStrCollection - a collection of owned strings that preserves insertion
// order, unlike TStringCollection which sorts its items.
class TStrCollection : public TCollection {

public:

    TStrCollection( short aLimit, short aDelta ) noexcept;

private:

    virtual void freeItem( void *item );

    virtual const char *streamableName() const
        { return name; }
    virtual void *readItem( ipstream& );
    virtual void writeItem( void *, opstream& );

protected:

    TStrCollection( StreamableInit ) noexcept : TCollection( streamableInit ) {}

public:

    static const char * const _NEAR name;
    static TStreamable *build();

};

inline ipstream& operator >> ( ipstream& is, TStrCollection& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TStrCollection*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TStrCollection& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TStrCollection* cl )
    { return os << (TStreamable *)cl; }
