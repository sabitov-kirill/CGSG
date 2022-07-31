/* FILE NAME  : binary_reader.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Binary reader type declaration module.
 */

#ifndef __binary_reader_h_
#define __binary_reader_h_

#include "../kigl.h"
#include <string>
#include <fstream>

namespace kigl
{
  // Forward declaration
  class material;

  /* Unstructured data file reader class */
  class binary_reader
  {
  private:
    // Memory pointer reference
    BYTE *Mem, *Ptr;
    INT FileLengthPriv;
    BOOL IsLoadedSuccsess;

  public:
    // Reading file length
    const INT &FileLength;

    /* Class constructor.
      * ARGUMENTS:
      *   - file name to read;
      */
    binary_reader( const std::string &FileName ) : 
      Mem(nullptr), Ptr(nullptr), IsLoadedSuccsess(FALSE),
      FileLengthPriv(0), FileLength(FileLengthPriv)
    {
      std::fstream file(FileName, std::fstream::in | std::fstream::binary);
      if (!file.is_open())
        return;

      // Check file length
      file.seekg(0, std::fstream::end);
      FileLengthPriv = (INT)file.tellg();
      file.seekg(0, std::fstream::beg);

      // Allocating memory, reading file
      Mem = new BYTE[FileLengthPriv], Ptr = Mem;
      file.read((CHAR *)Mem, FileLengthPriv);

      file.close();
      IsLoadedSuccsess = TRUE;
    } /* End of 'binary_reader' function */

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~binary_reader( VOID )
    {
      if (Mem != nullptr)
        delete[] Mem;
    } /* End of 'binary_reader' function */

    /* Binary readed loading state getting function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) loading flag.
     */
    BOOL IsOk( VOID )
    {
      return IsLoadedSuccsess;
    } // End of 'IsOk' function

    /* Read data function.
      * ARGUMENT:
      *   - read data pointer:
      *       type *Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
          *Data = *(type *)Ptr, Ptr += sizeof(type);
        else
          memcpy(Data, (type *)Ptr, sizeof(type) * Count), Ptr += sizeof(type) * Count;
      } /* End of 'operator()' function */
  }; /* End of 'rdr' class */
}

#endif // !__binary_reader_h_

// END OF 'binary_reader.h' FILE