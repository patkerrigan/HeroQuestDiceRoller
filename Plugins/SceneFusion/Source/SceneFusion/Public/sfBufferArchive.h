#pragma once

#include <CoreMinimal.h>
#include <Serialization/BufferArchive.h>
#include <Serialization/BufferReader.h>
#include <CoreMinimal.h>

/**
 * Serializer that serializes UObject* as sfObject ids or asset path.
 */
class sfBufferArchive : public FBufferArchive
{
public:
    /**
     * Tries to serialize a uobject reference by its sfObject id or asset path.
     * 
     * @param   UObject*& uobjPtr reference to serialize.
     * @return  FArchive& this
     */
    virtual FArchive& operator<<(UObject*& uobjPtr) override;

    /**
     * @return  const TSet<uint32_t>& String table ids for missing asset paths the serializer encountered.
     */
    const TSet<uint32_t>& MissingPathIds();

private:
    TSet<uint32_t> m_missingPathIds;
};

/**
 * Deserializer that deserializes UObject* from sfObject ids or asset paths.
 */
class sfBufferReader : public FBufferReaderBase
{
public:
    /**
     * Constructor
     *
     * @param   void* data to deserialize from.
     * @param   int64_t size of the data.
     */
    sfBufferReader(void* data, int64_t size);

    /**
     * Tries to deserialize a uobject reference from an sfObject id or asset path.
     *
     * @param   UObject*& uobjPtr to deserialize.
     * @return  FArchive& this
     */
    virtual FArchive& operator<<(UObject*& uobjPtr) override;

    /**
     * Deserializes an FName from a string.
     *
     * @param   FName& name to deserialize.
     * @return  FArchive& this
     */
    virtual FArchive& operator<<(FName& name) override;

    /**
     * @return  const TSet<uint32_t>& String table ids for missing asset paths the serializer encountered.
     */
    const TSet<uint32_t>& MissingPathIds();

private:
    TSet<uint32_t> m_missingPathIds;
};