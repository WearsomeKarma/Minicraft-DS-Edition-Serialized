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
    ISerializeable *ptr_serializeable;
    if ((ptr_serializeable = std::dynamic_pointer_cast<ISerializeable>(ptr)))
    {
      ptr_serializeable->serialize(*this);
      if(getError() != EK_NO_ERROR)
        return false;
    }
    if (!fread(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_READ;
      free(ptr);
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
      *addr_start = loadFromFile<TPtr>();
    } while(addr_start++ <= addr_end);
    return getError() == EK_NO_ERROR;
  }
  template<typename TPtr>
  TPtr *loadFromFile_Lookahead()
  {
    unsigned int location = ftell(file);
    TPtr ptr = new TPtr();
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
  template<typename TValue>
  bool loadFromFile_Vector(std::vector<TValue> &vec)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      vec.emplace_back();
      if (!loadFromFile(&vec.back()))
        return false;
    }
    return true;
  }
  template<typename TValue>
  bool loadFromFile_Vector_Shared(std::vector<std::shared_ptr<TValue>> &vec)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      vec.emplace_back();
      if (!loadFromFile(vec.back().get()))
        return false;
    }
    return true;
  }
  template<typename TPtr>
  bool saveToFile(TPtr *ptr)
  {
    ISerializeable *ptr_serializeable;
    if ((ptr_serializeable = std::dynamic_pointer_cast<ISerializeable>(ptr)))
    {
      ptr_serializeable->serialize(*this);
      return getError() == EK_NO_ERROR;
    }
    if (!fwrite(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_WRITE;
      return false;
    }
    return true;
  }
  template<typename TValue>
  bool saveToFile_Vector(std::vector<TValue> &vec)
  {
    size_t length = vec.size();
    if (!saveToFile(&length))
      return false;
    for (auto &entry : vec)
    {
      if (!saveToFile(&entry))
        return false;
    }
    return true;
  }
  template<typename TValue>
  bool saveToFile_Vector_Shared(std::vector<std::shared_ptr<TValue>> &vec)
  {
    size_t length = vec.size();
    if (!saveToFile(&length))
      return false;
    for (auto &entry : vec)
    {
      if (!saveToFile(entry.get()))
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
