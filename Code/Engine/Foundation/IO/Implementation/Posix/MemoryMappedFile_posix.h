#include <Foundation/IO/MemoryMappedFile.h>
#include <Foundation/Logging/Log.h>
#include <Foundation/Strings/PathUtils.h>

/// \todo Implement ezMemoryMappedFile on POSIX

struct ezMemoryMappedFileImpl
{
  ezMemoryMappedFile::Mode m_Mode = ezMemoryMappedFile::Mode::None;
  void* m_pMappedFilePtr = nullptr;
  ezUInt64 m_uiFileSize = 0;

  ~ezMemoryMappedFileImpl() { EZ_ASSERT_NOT_IMPLEMENTED; }
};

ezMemoryMappedFile::ezMemoryMappedFile()
{
  m_Impl = EZ_DEFAULT_NEW(ezMemoryMappedFileImpl);
}

ezMemoryMappedFile::~ezMemoryMappedFile()
{
  Close();
}

ezResult ezMemoryMappedFile::Open(const char* szAbsolutePath, Mode mode)
{
  EZ_ASSERT_NOT_IMPLEMENTED;
  return EZ_FAILURE;
}

void ezMemoryMappedFile::Close()
{
  m_Impl = EZ_DEFAULT_NEW(ezMemoryMappedFileImpl);
}

ezMemoryMappedFile::Mode ezMemoryMappedFile::GetMode() const
{
  return m_Impl->m_Mode;
}

const void* ezMemoryMappedFile::GetReadPointer() const
{
  EZ_ASSERT_DEBUG(m_Impl->m_Mode >= Mode::ReadOnly, "File must be opened with read access before accessing it for reading.");
  return m_Impl->m_pMappedFilePtr;
}

void* ezMemoryMappedFile::GetWritePointer()
{
  EZ_ASSERT_DEBUG(m_Impl->m_Mode >= Mode::ReadWrite, "File must be opened with read/write access before accessing it for writing.");
  return m_Impl->m_pMappedFilePtr;
}

ezUInt64 ezMemoryMappedFile::GetFileSize() const
{
  return m_Impl->m_uiFileSize;
}