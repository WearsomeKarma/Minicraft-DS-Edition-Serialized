#pragma once

#include "FactoryUUID.h"
#include "serializable.h"
#include <memory>
#include <stdio.h>
#include <vector>
#include <string>

class Game;

class Serializer
{
public:
  enum ErrorKind
  {
    EK_NO_ERROR,
    EK_MEMORY,
    EK_NO_FILE,
    EK_FAIL_WRITE,
    EK_FAIL_READ,
    EK_DOUBLE_OPEN,
    EK_DOUBLE_CLOSE,
    EK_GENERAL_IO,
    EK_LEAK,
  };
private:
  friend class UUID;
  friend class Level;
  Game &game;
private:
  FILE *file = nullptr;
  enum ErrorKind errorKind = EK_NO_ERROR; 
public:
  Serializer(Game &game) : game(game) {}

  bool openRead(const std::string &path) 
  {
    printf("\x1b[10;0HOPEN %s            ", path.c_str());
    if (file)
    {
      errorKind = EK_DOUBLE_OPEN;
      return false;
    }
    file = fopen("minicraft.dat", "r");
    if (!file)
    {
      errorKind = EK_NO_FILE;
      return false;
    }
    return true;
  }

  bool openWrite(const std::string &path) 
  {
    printf("\x1b[10;0HOPEN %s            ", path.c_str());
    if (file)
    {
      errorKind = EK_DOUBLE_OPEN;
      return false;
    }
    file = fopen("minicraft.dat", "w+");
    if (!file)
    {
      errorKind = EK_NO_FILE;
      return false;
    }
    return true;
  }

  bool close()
  {
    printf("\x1b[10;0HCLOSE %08lx          ", ftell(file));
    if(!file)
    {
      errorKind = EK_DOUBLE_CLOSE;
      return false;
    }
    if(!fclose(file))
    {
      errorKind = EK_GENERAL_IO;
      return false;
    }
    return true;
  }

  ~Serializer() { close(); }

  bool isClosed() { return file == nullptr; }
  size_t getPositionInFile() { return ftell(file); }

  enum ErrorKind getError() { return errorKind; }
  bool hasError() { return errorKind != EK_NO_ERROR; }

  template<typename TPtr>
  bool loadFromFile(TPtr *ptr)
  {
    printf("\x1b[10;0HLOAD %08lx            ", ftell(file));
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
  bool loadFromFile_Shared(std::shared_ptr<TPtr> &managed_ptr)
  {
    TPtr *ptr = new TPtr();
    if (!loadFromFile(ptr))
      return false;
    managed_ptr = std::shared_ptr<TPtr>(ptr);
    return true;
  }
  template<typename TPtr>
  bool loadFromFile_Shared_Serialized(std::shared_ptr<TPtr> &managed_ptr)
  {
    TPtr *ptr = new TPtr(*this);
    if (!ptr)
    {
      errorKind = EK_MEMORY;
      return false;
    }
    if (errorKind != EK_NO_ERROR)
    {
      delete ptr;
      return false;
    }
    managed_ptr = std::shared_ptr<TPtr>(ptr);
    return true;
  }
  template<typename TPtr, typename TContainer>
  bool loadFromFile_EmplaceBack(TContainer &container)
  {
    container.emplace_back();
    TPtr *ptr = &container.back();
    if(loadFromFile(ptr))
      return true;
    container.erase(container.end());
    return false;
  }
  template<typename TPtr, typename TContainer>
  bool loadFromFile_EmplaceBack_Shared(TContainer &container)
  {
    container.emplace_back();
    std::shared_ptr<TPtr> ptr = container.back();
    if(loadFromFile(ptr.get()))
      return true;
    container.erase(container.end());
    return false;
  }
  template<typename TPtr, typename TContainer>
  bool loadFromFile_EmplaceBack_Serialized(TContainer &container)
  {
    container.emplace_back(*this);
    if (errorKind == EK_NO_ERROR)
      return true;
    container.erase(container.end());
    return false;
  }
  // This is given as a courtesy. Be careful with it.
  // Fields must come one after another, and be of the same type.
  template<typename TPtr>
  bool loadFromFile_Fields(TPtr *addr_start, TPtr *addr_end)
  {
    // do
    // {
    //   if (!loadFromFile<TPtr>(addr_start))
    //     return false;
    // } while(addr_start++ <= addr_end);
    if (!fread(addr_start, sizeof(TPtr), addr_end - addr_start, file))
    {
      errorKind = EK_FAIL_READ;
      return false;
    }
    return true;
  }
  template<typename TPtr>
  bool loadFromFile_Lookahead(TPtr *&ptr)
  {
    if (ptr)
    {
      errorKind = EK_LEAK;
      return false;
    }
    unsigned int location = ftell(file);
    ptr = new TPtr();
    if (!ptr)
    {
      errorKind = EK_MEMORY;
      return false;
    }
    if (!fread(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_READ;
      free(ptr);
      return false;
    }
    fseek(file, location, SEEK_SET);
    return ptr;
  }
  template<typename TPtr>
  bool loadFromFile_Lookahead_Serialized(TPtr *&ptr)
  {
    if (ptr)
    {
      errorKind = EK_LEAK;
      return false;
    }
    unsigned int location = ftell(file);
    ptr = new TPtr(*this);
    if (!ptr)
    {
      errorKind = EK_MEMORY;
      return false;
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
    TValue buffer[length];
    if (!loadFromFile_Fields(buffer, buffer + length))
      return false;
    collection.insert(collection.end(), buffer, buffer + length);
    return true;
  }
  template<typename TCollection, typename TValue>
  bool loadFromFile_Collection_Shared(TCollection &collection)
  {
    size_t length;
    if (!loadFromFile(&length))
      return false;
    TValue buffer[] = new TValue[length];
    if (!loadFromFile_Fields(buffer, buffer + length))
    {
      delete[] buffer;
      return false;
    }
    for (size_t i=0;i<length;i++)
    {
      // printf("\x1b[11;0HCOLLECTION %ld            ", i);
      collection.push_back(std::shared_ptr<TValue>(buffer[i]));
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool loadFromFile_Collection_Serialized(TCollection &collection)
  {
    //TODO: make static getSizeInBytes() in TValue
    //      then make a byte buffer based on that size
    //      to limit the utilization of IO calls.
    size_t length;
    if (!loadFromFile(&length))
      return false;
    for (size_t i=0;i<length;i++)
    {
      printf("\x1b[11;0HCOLLECTION %ld / %ld           ", i, length);
      printf("\x1b[1;0HLOAD-collection-ser       ");
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
      printf("\x1b[11;0HCOLLECTION %ld / %ld           ", i, length);
      printf("\x1b[1;0HLOAD-collection-shr-ser       ");
      collection.push_back(std::make_shared<TValue>(*this));
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
  template<typename TPtr>
  bool saveToFile(TPtr *ptr)
  {
    printf("\x1b[10;0HSAVE %ld            ", ftell(file));
    if (!fwrite(ptr, sizeof(TPtr), 1, file))
    {
      errorKind = EK_FAIL_WRITE;
      return false;
    }
    return true;
  }
  bool saveToFile(ISerializeable *ptr)
  {
    printf("\x1b[10;0HSAVE-SER %ld            ", ftell(file));
    ptr->serialize(*this);
    return errorKind == EK_NO_ERROR;
  }
  // This is given as a courtesy. Be careful with it.
  // Fields must come one after another, and be of the same type.
  template<typename TPtr>
  bool saveToFile_Fields(TPtr *addr_start, TPtr *addr_end)
  {
    if (!fwrite(addr_start, sizeof(TPtr), addr_end - addr_start, file))
    {
      errorKind = EK_FAIL_WRITE;
      return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection(TCollection &collection)
  {
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    if (!saveToFile_Fields(collection.data(), collection.data() + collection.size()))
      return false;
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection_Serialized(TCollection &collection)
  {
    //TODO: same thing has the other TODO regarding
    //      static getSizeInBytes() but here.
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    size_t i = 0;
    for (TValue &entry : collection)
    {
      printf("\x1b[11;0HCOLLECTION %ld            ", i++);
      entry.serialize(*this);
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection_Shared(TCollection &collection)
  {
    //TODO: do similar buffering for IO here.
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    size_t i = 0;
    for (std::shared_ptr<TValue> &entry : collection)
    {
      printf("\x1b[11;0HCOLLECTION %ld            ", i++);
      if (!saveToFile(entry.get()))
        return false;
    }
    return true;
  }
  template<typename TCollection, typename TValue>
  bool saveToFile_Collection_Shared_Serialized(TCollection &collection)
  {
    //TODO: same thing here.
    size_t length = collection.size();
    if (!saveToFile(&length))
      return false;
    size_t i = 0;
    for (std::shared_ptr<TValue> &entry : collection)
    {
      printf("\x1b[11;0HCOLLECTION %ld %08lx           ", i++, ftell(file));
      entry->serialize(*this);
      if (errorKind != EK_NO_ERROR)
        return false;
    }
    return true;
  }
};
