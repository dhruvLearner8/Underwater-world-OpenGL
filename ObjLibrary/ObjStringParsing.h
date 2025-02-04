//
//  ObjStringParsing.h
//
//  A set of functions used in parsing OBJ files.
//
//  This file is part of the ObjLibrary, by Richard Hamilton,
//    which is copyright Hamilton 2009-2024.
// 
//  You may use these files for any purpose as long as you do
//    not explicitly claim them as your own work or object to
//    other people using them.
// 
//  If you are distributing the source files, you must not
//    remove this notice.  If you are only distributing compiled
//    code, no credit is required.
// 
//  A (theoretically) up-to-date version of the ObjLibrary can
//    be found at:
//  http://infiniplix.ca/resources/obj_library/
//

#ifndef OBJ_LIBRARY_OBJ_STRING_PARSING_H
#define OBJ_LIBRARY_OBJ_STRING_PARSING_H

#include <string>



namespace ObjLibrary
{



//
//  ObjStringParsing
//
//  A namespace containing string-handling functions used in
//    parsing OBJ files.  And other related files.
//
namespace ObjStringParsing
{
//
//  nextToken
//
//  Purpose: To determine the index of the next token character
//           in the specified string.  The next token is here
//           defined to start with next non-whitespace character
//           following a whitespace character at or after the
//           current position.
//  Parameter(s):
//    <1> str: The string to search
//    <2> current: The index to begin searching at
//  Precondition(s): N/A
//  Returns: The index of the beginning of the next token.  If
//           there is no next token, string::npos is returned.
//  Side Effect: N/A
//
size_t nextToken (const std::string& str, size_t current);

//
//  getTokenLength
//
//  Purpose: To determine the length of the token starting with
//           the specified character in the specified string.
//           The token length is here defined as the number of
//           characters, including the specified character,
//            before the next whitespace character.
//  Parameter(s):
//    <1> str: The string to search
//    <2> current: The beginning of the token
//  Precondition(s): N/A
//  Returns: The length of the token beginning with current.  If
//           current is a whitespace character or lies outside
//           of str, 0 is returned.
//  Side Effect: N/A
//
size_t getTokenLength (const std::string& str, size_t current);

//
//  nextSlashInToken
//
//  Purpose: To determine the index of the next slash ('/')
//           character in the current token of the specified
//           string, and after the specified position.
//  Parameter(s):
//    <1> str: The string to search
//    <2> current: The index to begin searching at
//  Precondition(s): N/A
//  Returns: The index of the next slash in this token.  If
//           there is no next slash, string::npos is returned.
//  Side Effect: N/A
//
size_t nextSlashInToken(const std::string& str, size_t current);



//
//  toLowercase
//
//  Purpose: To convert the specified string to lowercase.
//  Parameter(s):
//    <1> str: The string to convert
//  Precondition(s): N/A
//  Returns: str in lowercase.
//  Side Effect: N/A
//
std::string toLowercase (const std::string& str);

//
//  whitespaceToSpaces
//
//  Purpose: To replace all whitespace chacacters in the
//           specified string to ' ' characters.  This should
//           simplify comparisons with the string.
//  Parameter(s):
//    <1> str: The string to convert
//  Precondition(s): N/A
//  Returns: A copy of str with all whitespace characters
//           converted to spaces.
//  Side Effect: N/A
//
std::string whitespaceToSpaces (const std::string& str);



//
//  endsWith
//
//  Purpose: To determine if the specified string ends with the
//           specified C-string.
//  Parameter(s):
//    <1> str: The string to test
//    <2> a_end: The end C-string
//  Precondition(s):
//    <1> a_end != NULL
//  Returns: Whether str ends with end.
//  Side Effect: N/A
//
bool endsWith (const std::string& str, const char* a_end);

//
//  endsWith
//
//  Purpose: To determine if the specified string ends with the
//           specified other string.
//  Parameter(s):
//    <1> str: The string to test
//    <2> end: The end string
//  Precondition(s): N/A
//  Returns: Whether str ends with end.
//  Side Effect: N/A
//
bool endsWith (const std::string& str, const std::string& end);

//
//  startsWith
//
//  Purpose: To determine if the specified string starts with
//           the specified C-string.
//  Parameter(s):
//    <1> str: The string to test
//    <2> a_start: The end C-string
//  Precondition(s):
//    <1> a_start != NULL
//  Returns: Whether str starts with end.
//  Side Effect: N/A
//
bool startsWith (const std::string& str, const char* a_start);

//
//  startsWith
//
//  Purpose: To determine if the specified string starts with
//           the specified other string.
//  Parameter(s):
//    <1> str: The string to test
//    <2> start: The end string
//  Precondition(s): N/A
//  Returns: Whether str starts with start.
//  Side Effect: N/A
//
bool startsWith (const std::string& str,
                 const std::string& start);



//
//  isValidFilenameWithPath
//
//  Purpose: To determine if the specified string is a valid
//           filename.  This function allows the filename to
//           have an attached path.  If you want to ensure that
//           there is only a filename, use the isValidFilename
//           function.
//  Parameter(s):
//    <1> filename: The filename to test
//  Precondition(s): N/A
//  Returns: Whether filename is a valid filename or
//           filename-including-path.  A filename must not be
//           the empty string or end with a slash (or
//           backslash).
//  Side Effect: N/A
//
bool isValidFilenameWithPath (const std::string& filename);

//
//  isValidFilename
//
//  Purpose: To determine if the specified string is a valid
//           filename.  This function checks for a filename
//           without an attached path.  If a path should be
//           allowed, use the isValidFilenameWithPath function.
//  Parameter(s):
//    <1> filename: The filename to test
//  Precondition(s): N/A
//  Returns: Whether filename is a valid filename.  A filename
//           must not be the empty string or contian any slashes
//           (or backslashes).
//  Side Effect: N/A
//
bool isValidFilename (const std::string& filename);

//
//  isValidPath
//
//  Purpose: To determine if the specified string is a valid
//           path to prepend onto filenames.
//  Parameter(s):
//    <1> path: The path to test
//  Precondition(s): N/A
//  Returns: Whether path is a valid filename path.  The empty
//           string is considered to be a valid path.
//  Side Effect: N/A
//
bool isValidPath (const std::string& path);

//
//  separatePathOutOfFilename
//
//  Purpose: To convert the specified filename and possible
//           attached path into a path and a filename without a
//           path.
//  Parameter(s):
//    <1> filename_with_path: The combined path and file name
//    <2> r_filename: A reference to fill with the file name
//    <3> r_path: A reference to fill with the file path
//  Precondition(s): N/A
//    <1> isValidFilenameWithPath(filename_with_path)
//  Returns: N/A
//  Side Effect: If there is a path in filename_with_path,
//               r_path is set to it and r_filename is set to
//               the remainder of filename_with_path (without
//               the separator).  Otherwise, r_path is set
//               to the empty string and r_filename is set to
//               filename_with_path.  In either case, the value
//               of r_filename will always be a valid filename
//               and the value of r_path will always be a valid
//               file path.
//
void separatePathOutOfFilename (
                          const std::string& filename_with_path,
                          std::string& r_filename,
                          std::string& r_path);

}  // end of namespace ObjStringParsing



}  // end of namespace ObjLibrary

#endif
