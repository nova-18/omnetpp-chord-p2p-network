//
// Generated file, do not edit! Created by opp_msgtool 6.1 from message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "message_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(subtask)

subtask::subtask(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

subtask::subtask(const subtask& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

subtask::~subtask()
{
    delete [] this->query;
}

subtask& subtask::operator=(const subtask& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void subtask::copy(const subtask& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->queryLen = other.queryLen;
    delete [] this->query;
    this->query = (other.query_arraysize==0) ? nullptr : new int[other.query_arraysize];
    query_arraysize = other.query_arraysize;
    for (size_t i = 0; i < query_arraysize; i++) {
        this->query[i] = other.query[i];
    }
    this->TaskNum = other.TaskNum;
    this->subTaskNum = other.subTaskNum;
    this->timestamp = other.timestamp;
}

void subtask::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->queryLen);
    b->pack(query_arraysize);
    doParsimArrayPacking(b,this->query,query_arraysize);
    doParsimPacking(b,this->TaskNum);
    doParsimPacking(b,this->subTaskNum);
    doParsimPacking(b,this->timestamp);
}

void subtask::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->queryLen);
    delete [] this->query;
    b->unpack(query_arraysize);
    if (query_arraysize == 0) {
        this->query = nullptr;
    } else {
        this->query = new int[query_arraysize];
        doParsimArrayUnpacking(b,this->query,query_arraysize);
    }
    doParsimUnpacking(b,this->TaskNum);
    doParsimUnpacking(b,this->subTaskNum);
    doParsimUnpacking(b,this->timestamp);
}

int subtask::getSourceId() const
{
    return this->sourceId;
}

void subtask::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int subtask::getDestId() const
{
    return this->destId;
}

void subtask::setDestId(int destId)
{
    this->destId = destId;
}

int subtask::getQueryLen() const
{
    return this->queryLen;
}

void subtask::setQueryLen(int queryLen)
{
    this->queryLen = queryLen;
}

size_t subtask::getQueryArraySize() const
{
    return query_arraysize;
}

int subtask::getQuery(size_t k) const
{
    if (k >= query_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)query_arraysize, (unsigned long)k);
    return this->query[k];
}

void subtask::setQueryArraySize(size_t newSize)
{
    int *query2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = query_arraysize < newSize ? query_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        query2[i] = this->query[i];
    for (size_t i = minSize; i < newSize; i++)
        query2[i] = 0;
    delete [] this->query;
    this->query = query2;
    query_arraysize = newSize;
}

void subtask::setQuery(size_t k, int query)
{
    if (k >= query_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)query_arraysize, (unsigned long)k);
    this->query[k] = query;
}

void subtask::insertQuery(size_t k, int query)
{
    if (k > query_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)query_arraysize, (unsigned long)k);
    size_t newSize = query_arraysize + 1;
    int *query2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        query2[i] = this->query[i];
    query2[k] = query;
    for (i = k + 1; i < newSize; i++)
        query2[i] = this->query[i-1];
    delete [] this->query;
    this->query = query2;
    query_arraysize = newSize;
}

void subtask::appendQuery(int query)
{
    insertQuery(query_arraysize, query);
}

void subtask::eraseQuery(size_t k)
{
    if (k >= query_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)query_arraysize, (unsigned long)k);
    size_t newSize = query_arraysize - 1;
    int *query2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        query2[i] = this->query[i];
    for (i = k; i < newSize; i++)
        query2[i] = this->query[i+1];
    delete [] this->query;
    this->query = query2;
    query_arraysize = newSize;
}

int subtask::getTaskNum() const
{
    return this->TaskNum;
}

void subtask::setTaskNum(int TaskNum)
{
    this->TaskNum = TaskNum;
}

int subtask::getSubTaskNum() const
{
    return this->subTaskNum;
}

void subtask::setSubTaskNum(int subTaskNum)
{
    this->subTaskNum = subTaskNum;
}

omnetpp::simtime_t subtask::getTimestamp() const
{
    return this->timestamp;
}

void subtask::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class subtaskDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_queryLen,
        FIELD_query,
        FIELD_TaskNum,
        FIELD_subTaskNum,
        FIELD_timestamp,
    };
  public:
    subtaskDescriptor();
    virtual ~subtaskDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(subtaskDescriptor)

subtaskDescriptor::subtaskDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(subtask)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

subtaskDescriptor::~subtaskDescriptor()
{
    delete[] propertyNames;
}

bool subtaskDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<subtask *>(obj)!=nullptr;
}

const char **subtaskDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *subtaskDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int subtaskDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int subtaskDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_queryLen
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_query
        FD_ISEDITABLE,    // FIELD_TaskNum
        FD_ISEDITABLE,    // FIELD_subTaskNum
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *subtaskDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "queryLen",
        "query",
        "TaskNum",
        "subTaskNum",
        "timestamp",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int subtaskDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "queryLen") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "query") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "TaskNum") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "subTaskNum") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *subtaskDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_destId
        "int",    // FIELD_queryLen
        "int",    // FIELD_query
        "int",    // FIELD_TaskNum
        "int",    // FIELD_subTaskNum
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **subtaskDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *subtaskDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int subtaskDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        case FIELD_query: return pp->getQueryArraySize();
        default: return 0;
    }
}

void subtaskDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        case FIELD_query: pp->setQueryArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'subtask'", field);
    }
}

const char *subtaskDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string subtaskDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_queryLen: return long2string(pp->getQueryLen());
        case FIELD_query: return long2string(pp->getQuery(i));
        case FIELD_TaskNum: return long2string(pp->getTaskNum());
        case FIELD_subTaskNum: return long2string(pp->getSubTaskNum());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void subtaskDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_queryLen: pp->setQueryLen(string2long(value)); break;
        case FIELD_query: pp->setQuery(i,string2long(value)); break;
        case FIELD_TaskNum: pp->setTaskNum(string2long(value)); break;
        case FIELD_subTaskNum: pp->setSubTaskNum(string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'subtask'", field);
    }
}

omnetpp::cValue subtaskDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_queryLen: return pp->getQueryLen();
        case FIELD_query: return pp->getQuery(i);
        case FIELD_TaskNum: return pp->getTaskNum();
        case FIELD_subTaskNum: return pp->getSubTaskNum();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'subtask' as cValue -- field index out of range?", field);
    }
}

void subtaskDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_queryLen: pp->setQueryLen(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_query: pp->setQuery(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_TaskNum: pp->setTaskNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_subTaskNum: pp->setSubTaskNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'subtask'", field);
    }
}

const char *subtaskDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr subtaskDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void subtaskDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    subtask *pp = omnetpp::fromAnyPtr<subtask>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'subtask'", field);
    }
}

Register_Class(subtaskResp)

subtaskResp::subtaskResp(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

subtaskResp::subtaskResp(const subtaskResp& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

subtaskResp::~subtaskResp()
{
}

subtaskResp& subtaskResp::operator=(const subtaskResp& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void subtaskResp::copy(const subtaskResp& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->answer = other.answer;
    this->TaskNum = other.TaskNum;
    this->SubTaskNum = other.SubTaskNum;
    this->timestamp = other.timestamp;
}

void subtaskResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->answer);
    doParsimPacking(b,this->TaskNum);
    doParsimPacking(b,this->SubTaskNum);
    doParsimPacking(b,this->timestamp);
}

void subtaskResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->answer);
    doParsimUnpacking(b,this->TaskNum);
    doParsimUnpacking(b,this->SubTaskNum);
    doParsimUnpacking(b,this->timestamp);
}

int subtaskResp::getSourceId() const
{
    return this->sourceId;
}

void subtaskResp::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int subtaskResp::getDestId() const
{
    return this->destId;
}

void subtaskResp::setDestId(int destId)
{
    this->destId = destId;
}

int subtaskResp::getAnswer() const
{
    return this->answer;
}

void subtaskResp::setAnswer(int answer)
{
    this->answer = answer;
}

int subtaskResp::getTaskNum() const
{
    return this->TaskNum;
}

void subtaskResp::setTaskNum(int TaskNum)
{
    this->TaskNum = TaskNum;
}

int subtaskResp::getSubTaskNum() const
{
    return this->SubTaskNum;
}

void subtaskResp::setSubTaskNum(int SubTaskNum)
{
    this->SubTaskNum = SubTaskNum;
}

omnetpp::simtime_t subtaskResp::getTimestamp() const
{
    return this->timestamp;
}

void subtaskResp::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class subtaskRespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_answer,
        FIELD_TaskNum,
        FIELD_SubTaskNum,
        FIELD_timestamp,
    };
  public:
    subtaskRespDescriptor();
    virtual ~subtaskRespDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(subtaskRespDescriptor)

subtaskRespDescriptor::subtaskRespDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(subtaskResp)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

subtaskRespDescriptor::~subtaskRespDescriptor()
{
    delete[] propertyNames;
}

bool subtaskRespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<subtaskResp *>(obj)!=nullptr;
}

const char **subtaskRespDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *subtaskRespDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int subtaskRespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int subtaskRespDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_answer
        FD_ISEDITABLE,    // FIELD_TaskNum
        FD_ISEDITABLE,    // FIELD_SubTaskNum
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *subtaskRespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "answer",
        "TaskNum",
        "SubTaskNum",
        "timestamp",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int subtaskRespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "answer") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "TaskNum") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "SubTaskNum") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *subtaskRespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_destId
        "int",    // FIELD_answer
        "int",    // FIELD_TaskNum
        "int",    // FIELD_SubTaskNum
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **subtaskRespDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *subtaskRespDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int subtaskRespDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void subtaskRespDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'subtaskResp'", field);
    }
}

const char *subtaskRespDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string subtaskRespDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_answer: return long2string(pp->getAnswer());
        case FIELD_TaskNum: return long2string(pp->getTaskNum());
        case FIELD_SubTaskNum: return long2string(pp->getSubTaskNum());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void subtaskRespDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_answer: pp->setAnswer(string2long(value)); break;
        case FIELD_TaskNum: pp->setTaskNum(string2long(value)); break;
        case FIELD_SubTaskNum: pp->setSubTaskNum(string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'subtaskResp'", field);
    }
}

omnetpp::cValue subtaskRespDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_answer: return pp->getAnswer();
        case FIELD_TaskNum: return pp->getTaskNum();
        case FIELD_SubTaskNum: return pp->getSubTaskNum();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'subtaskResp' as cValue -- field index out of range?", field);
    }
}

void subtaskRespDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_answer: pp->setAnswer(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_TaskNum: pp->setTaskNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_SubTaskNum: pp->setSubTaskNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'subtaskResp'", field);
    }
}

const char *subtaskRespDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr subtaskRespDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void subtaskRespDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    subtaskResp *pp = omnetpp::fromAnyPtr<subtaskResp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'subtaskResp'", field);
    }
}

Register_Class(gossip)

gossip::gossip(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

gossip::gossip(const gossip& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

gossip::~gossip()
{
}

gossip& gossip::operator=(const gossip& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void gossip::copy(const gossip& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->TaskNum = other.TaskNum;
    this->TaskResult = other.TaskResult;
    this->GossipMsg = other.GossipMsg;
    this->timestamp = other.timestamp;
}

void gossip::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->TaskNum);
    doParsimPacking(b,this->TaskResult);
    doParsimPacking(b,this->GossipMsg);
    doParsimPacking(b,this->timestamp);
}

void gossip::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->TaskNum);
    doParsimUnpacking(b,this->TaskResult);
    doParsimUnpacking(b,this->GossipMsg);
    doParsimUnpacking(b,this->timestamp);
}

int gossip::getSourceId() const
{
    return this->sourceId;
}

void gossip::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int gossip::getDestId() const
{
    return this->destId;
}

void gossip::setDestId(int destId)
{
    this->destId = destId;
}

int gossip::getTaskNum() const
{
    return this->TaskNum;
}

void gossip::setTaskNum(int TaskNum)
{
    this->TaskNum = TaskNum;
}

int gossip::getTaskResult() const
{
    return this->TaskResult;
}

void gossip::setTaskResult(int TaskResult)
{
    this->TaskResult = TaskResult;
}

const char * gossip::getGossipMsg() const
{
    return this->GossipMsg.c_str();
}

void gossip::setGossipMsg(const char * GossipMsg)
{
    this->GossipMsg = GossipMsg;
}

omnetpp::simtime_t gossip::getTimestamp() const
{
    return this->timestamp;
}

void gossip::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class gossipDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_TaskNum,
        FIELD_TaskResult,
        FIELD_GossipMsg,
        FIELD_timestamp,
    };
  public:
    gossipDescriptor();
    virtual ~gossipDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(gossipDescriptor)

gossipDescriptor::gossipDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(gossip)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

gossipDescriptor::~gossipDescriptor()
{
    delete[] propertyNames;
}

bool gossipDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<gossip *>(obj)!=nullptr;
}

const char **gossipDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *gossipDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int gossipDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int gossipDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_TaskNum
        FD_ISEDITABLE,    // FIELD_TaskResult
        FD_ISEDITABLE,    // FIELD_GossipMsg
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *gossipDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "TaskNum",
        "TaskResult",
        "GossipMsg",
        "timestamp",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int gossipDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "TaskNum") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "TaskResult") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "GossipMsg") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *gossipDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_destId
        "int",    // FIELD_TaskNum
        "int",    // FIELD_TaskResult
        "string",    // FIELD_GossipMsg
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **gossipDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *gossipDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int gossipDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void gossipDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'gossip'", field);
    }
}

const char *gossipDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string gossipDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_TaskNum: return long2string(pp->getTaskNum());
        case FIELD_TaskResult: return long2string(pp->getTaskResult());
        case FIELD_GossipMsg: return oppstring2string(pp->getGossipMsg());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void gossipDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_TaskNum: pp->setTaskNum(string2long(value)); break;
        case FIELD_TaskResult: pp->setTaskResult(string2long(value)); break;
        case FIELD_GossipMsg: pp->setGossipMsg((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'gossip'", field);
    }
}

omnetpp::cValue gossipDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_TaskNum: return pp->getTaskNum();
        case FIELD_TaskResult: return pp->getTaskResult();
        case FIELD_GossipMsg: return pp->getGossipMsg();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'gossip' as cValue -- field index out of range?", field);
    }
}

void gossipDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_TaskNum: pp->setTaskNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_TaskResult: pp->setTaskResult(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_GossipMsg: pp->setGossipMsg(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'gossip'", field);
    }
}

const char *gossipDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr gossipDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void gossipDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    gossip *pp = omnetpp::fromAnyPtr<gossip>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'gossip'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

