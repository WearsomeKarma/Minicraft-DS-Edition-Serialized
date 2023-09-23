#pragma once

#include "serializable.h"
#include <memory>
#include <stdio.h>
#include <vector>

class Serializer
{
public:
  enum ErrorKind
  {
    EK_NO_ERROR,
    EK_MEMORY,
    EK_BAD_SIZE,
    EK_NO_FILE,
    EK_FAIL_WRITE,
    EK_FAIL_READ,
  };
private:
  FILE *file;
  enum ErrorKind errorKind = EK_NO_ERROR; 
public:
  enum ErrorKind getError() { return errorKind; }
  template<typename TPtr>
  bool loadFromFile(TPtr *ptr)
  {
    if (!ptr)
    {
      errorKind = EK_MEMORY;
      return false;
    }
    if (!fread(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_READ;
      return false;
    }
    return true;
  }
  template<typename TPtr>
  TPtr *loadFromFile()
  {
    TPtr *ptr = new TPtr();
    if (loadFromFile(ptr))
      return ptr;
    delete ptr;
    return NULL;
  }
  template<typename TPtr>
  std::shared_ptr<TPtr> loadFromFile_Shared()
  {
    TPtr *ptr = new TPtr();
    if (loadFromFile(ptr))
      return std::shared_ptr<TPtr>(ptr);
    return NULL;
  }
  template<typename TPtr, typename TContainer>
  void loadFromFile_EmplaceBack(TContainer &container)
  {
    container.emplace_back();
    TPtr *ptr = &container.back();
    loadFromFile(ptr);
  }
  template<typename TPtr, typename TContainer>
  void loadFromFile_EmplaceBack_Shared(TContainer &container)
  {
    container.emplace_back();
    std::shared_ptr<TPtr> ptr = container.back();
    loadFromFile(ptr.get());
  }
  // This is given as a courtesy. Be careful with it.
  // Fields must come one after another, and be of the same type.
  template<typename TPtr>
  bool loadFromFile_Fields(TPtr *addr_start, TPtr *addr_end)
  {
    do
    {
      loadFromFile<TPtr>(addr_start);
    } while(addr_start++ <= addr_end);
    return getError() == EK_NO_ERROR;
  }
  template<typename TPtr>
  TPtr *loadFromFile_Lookahead()
  {
    unsigned int location = ftell(file);
    TPtr *ptr = new TPtr();
    if (!ptr)
    {
      errorKind = EK_MEMORY;
      return NULL;
    }
    if (!fread(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_READ;
      free(ptr);
      return NULL;
    }
    fseek(file, location, SEEK_SET);
    return ptr;
  }
  template<typename TCollection, typename TValue>
  bool loadFromFile_Collection(TCollection &collection)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      collection.emplace_back();
      if (!loadFromFile(&collection.back()))
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool loadFromFile_Collection_Shared(TCollection &collection)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      collection.emplace_back();
      if (!loadFromFile(collection.back().get()))
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool loadFromFile_Collection_Serialized(TCollection &collection)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      collection.emplace_back(*this);
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool loadFromFile_Collection_Shared_Serialized(TCollection &collection)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      collection.push_back(std::make_shared<TValue>(*this));
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
  template<typename TPtr>
  bool saveToFile(TPtr *ptr)
  {
    if (!fwrite(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_WRITE;
      return false;
    }
    return true;
  }
  bool saveToFile(ISerializeable *ptr)
  {
    ptr->serialize(*this);
    return errorKind == EK_NO_ERROR;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection(TCollection &collection)
  {
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    for (TValue &entry : collection)
    {
      if (!saveToFile(&entry))
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection_Serialized(TCollection &collection)
  {
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    for (TValue &entry : collection)
    {
      entry.serialize(*this);
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection_Shared(TCollection &collection)
  {
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    for (std::shared_ptr<TValue> &entry : collection)
    {
      if (!saveToFile(entry.get()))
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection_Shared_Serialized(TCollection &collection)
  {
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    for (std::shared_ptr<TValue> &entry : collection)
    {
      entry->serialize(*this);
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
  // This is given as a courtesy. Be careful with it.
  // Fields must come one after another, and be of the same type.
  template<typename TPtr>
  bool saveToFile_Fields(TPtr *addr_start, TPtr *addr_end)
  {
    do
    {
      if (!saveToFile(addr_start))
        return false;
    } while(addr_start++ <= addr_end);
    return true;
  }
};
