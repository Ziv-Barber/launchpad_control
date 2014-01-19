
//
// Simple Helper Classes Library.
// Copyright (C) Ziv Barber.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//

///
/// @file
/// @brief Ziv Barber string parsing functions (header).
///
/// This is the header file of all the string parsing functions of Ziv Barber.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#ifndef H_STRING_PARSER_HEAD
#define H_STRING_PARSER_HEAD

//
// Header files needed to be include with this header:
//

#include "basedefs.h"

#include <string>

//
// Some public definess:
//

//
// Public prototypes:
//

///
/// @brief Compare operation of strings with many cool features.
///
/// Except for comparing the given string this method can also be used as a token parser and also 
/// for searching if one or more strings exists on the given input string.
///
/// @param[in] pInputString Pointer to the string to check. It don't have to be zero terminated string (refer to the iSizeOfInputString parameter for more information).
/// @param[in] pTokensString Pointer to the string to compare with. This string is a list of tokens if bIsTokensOperation is true. It don't have to be zero terminated string.
/// @param[in] iSizeOfInputString If this parameter is equal or greater then 0 then it's holding the number of characters on the pInputString buffer.
/// @param[in] iSizeOfTokenString If this parameter is equal or greater then 0 then it's holding the number of characters on the pTokensString buffer.
/// @param[in] bInsensitive Case insensitive operation.
/// @param[in] bIgnoreWhitespace Ignore whitespace characters.
/// @param[in] bIsTokensOperation Set it to true if pTokensString is pointing to a list of tokens.
/// @param[in] bEnableWildcard Enable or disable using of some wildcards characters (both '?' and '*' are supported).
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[in] bFindOperation Set it to true if you want to search for a string inside string.
/// @param[out] piOffsetToValue If this parameter is not equal to NULL then it'll be filled with the offset to the value's data.
/// @param[out] piValueSize If this parameter is not equal to NULL then it'll be filled with the size in characters of the value's data.
/// @param[out] piOffsetToToken If this parameter is not equal to NULL then it'll be filled with the offset to the name of the token been found.
/// @param[out] piTokenSize If this parameter is not equal to NULL then it'll be filled with the size in characters of the name of the token been found.
/// @retval -1 String not equal (or token not been found).
/// @retval else The index if the token been found.
///
int ExtendedCompare (
	char *pInputString,
	char *pTokensString,
	int iSizeOfInputString = -1,
	int iSizeOfTokenString = -1,
	bool bFindOperation = false,
	bool bInsensitive = false,
	bool bIgnoreWhitespace = false,
	bool bIsTokensOperation = false,
	bool bEnableWildcard = false,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	int *piOffsetToValue = NULL,
	int *piValueSize = NULL,
	int *piOffsetToToken = NULL,
	int *piTokenSize = NULL
	);

///
/// @brief Convert a string to boolean value.
///
/// This function understanding many kind of boolean text names.
///
/// @param[in] szValue The boolean value as text string.
/// @param[in] iSizeOfString The size of the string. This parameter can be equal to -1 to auto-detect the size of the string.
/// @return The parsed boolean value.
///
bool GetBooleanAsString (
	char *szValue,
	int iSizeOfString = -1
	);

///
/// @brief Conert string into number in any base.
///
/// This method convert a string filled with number in any base to an integer.
///
/// @param[in] szInput String to parse.
/// @param[in] iBase Base of the number or 0 to auto-detect.
/// @param[in] iStopHere Either size of the area on the string to parse in characters or 0 to parse all the string.
/// @param[out] pNext Will be filled with the next character on the string after the number. This parameter can be NULL if you don't need this feature.
/// @return Either number found inside the string or 0.
/// @see EncodeNumber
///
bs_uint64 DecodeNumber (
	const char *szInput,
	int iBase = 10,
	int iStopHere = 0,
	const char **pNext = NULL
	);

///
/// @brief Convert number to string.
///
/// This function convert the given number to string.
///
/// @param[out] szOutput Buffer to fill with the number as string.
/// @param[in] iSizeOfBuffer Size of the output buffer.
/// @param[in] iBase Base to use.
/// @param[in] iNumber Number to convert.
/// @param[in] bPrefix true to add also prefix that represents the base type (like 0x to hex number or 0 to octal numbers).
/// @param[in] bCase write any letter in uppercase.
/// @see DecodeNumber
///
void EncodeNumber (
	char *szOutput,
	int iSizeOfBuffer,
	int iBase,
	bs_uint64 iNumber,
	bool bPrefix = false,
	bool bCase = false
	);

///
/// @brief Find one of the given characters and also get the non whitespace string before it.
///
/// This method search for one of the characters on szCharsList and also fill 
/// oOutValue with the string before it not including the whitespace before 
/// and after the string.
///
/// @param[in] szValue The string to search on it.
/// @param[in] szCharsList List of characters to search for one of them.
/// @param[in] oOutValue Will be filled with the string before the character been found.
/// @param[in] uiValueSize The size of the szValue string.
/// @param[in] uiCharsSize The size of the szCharsList string.
/// @retval NULL Character not found.
/// @retval else Pointer to the character found inside the szValue string.
///
const char *FindUpToCharacter (
	const char *szValue,
	const char *szCharsList,
	std::string& oOutValue,
	unsigned int uiValueSize = (unsigned int) -1,
	unsigned int uiCharsSize = (unsigned int) -1
	);

///
/// @brief Locate the end of the current token and also the data of it.
///
/// This method help on breaking a token.
///
/// @param[in] szTokensString String filled with tokens.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] puiDataPos If this parameter is not equal to NULL then it'll be filled with the position of data value of this token. If there's no data value then this parameter will be filled with -1.
/// @param[in] puiDataSize If this parameter is not equal to NULL then it'll be filled with the size of data value of this token. If there's no data value then this parameter will be filled with 0.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @retval -1 No tokens.
/// @retval else the size in bytes of the token's name.
///
unsigned int GetTokenInfo (
	const char *szTokensString,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	unsigned int *puiDataPos = NULL,
	unsigned int *puiDataSize = NULL,
	char cSeparatorChar = ';',
	char cTokenValueChar = '='
	);

///
/// @brief Extract the real text without the whitespace.
///
/// This method find out where the real text inside the given string.
///
/// @param[in] szText The string to work on it.
/// @param[in] uiStrSize Either the size of the string in characters or -1 to auto calculate the size of the string.
/// @param[out] uiTextSize Will be filled with the size of the real text on the string.
/// @return Position to the first real character on the string.
///
unsigned int GetSizeOfWhiteSpace (
	const char *szText,
	unsigned int uiStrSize,
	unsigned int& uiTextSize
	);

///
/// @brief Locate a name on the given enum string.
///
/// This method locating the given name on the enum string and translate it to number.
///
/// @param[in] szEnumItem The name to find.
/// @param[in] szTokensString String filled with tokens.
/// @param[in] uiSizeOfEnumItem The size of the name to find.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[out] pbIsError If this parameter is not equal to NULL then it will be true on error.
/// @param[in] bFlagsOperation If this parameter is true then the token string is represending a mask flags list.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
/// @return The enum as number.
///
bs_uint64 TranslateEnumToValue (
	const char *szEnumItem,
	const char *szTokensString,
	unsigned int uiSizeOfEnumItem = (unsigned int) -1,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool *pbIsError = NULL,
	bool bFlagsOperation = false,
	bool bIgnoreCommands = false
	);

///
/// @brief Translate a value to name.
///
/// This method translate the given value into string.
///
/// @param[in] ullValue the value to translate.
/// @param[in] szTokensString String filled with tokens.
/// @param[out] uiSizeOfName On success will be filled with the size of the returned string.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[out] pbIsError If this parameter is not equal to NULL then it will be true on error.
/// @param[in] bFlagsOperation If this parameter is true then the token string is represending a mask flags list.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
/// @retval NULL Invalid value.
/// @retval else Pointer to the name string of this value on the tokens string.
///
const char *TranslateValueToName (
	bs_uint64 ullValue,
	const char *szTokensString,
	unsigned int& uiSizeOfName,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool *pbIsError = NULL,
	bool bFlagsOperation = false,
	bool bIgnoreCommands = false
	);

///
/// @brief Check if the given validation string represent a boolean.
///
/// This method check if the given tokens string represent a boolean.
///
/// @param[in] szTokensString String filled with tokens.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[out] pbIsError If this parameter is not equal to NULL then it will be true on error.
/// @param[in] bFlagsOperation If this parameter is true then the token string is represending a mask flags list.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
/// @retval true Boolean.
/// @retval false Not boolean.
///
bool CheckIfBooleanValidation (
	const char *szTokensString,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool *pbIsError = NULL,
	bool bFlagsOperation = false,
	bool bIgnoreCommands = false
	);

///
/// @brief Check if the given validation string is of enum.
///
/// Enum based validation is only allow to enter one or more list of 
/// pre-definded values.
///
/// @param[in] szTokensString String filled with tokens.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[out] pbIsError If this parameter is not equal to NULL then it will be true on error.
/// @param[in] bFlagsOperation If this parameter is true then the token string is represending a mask flags list.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
/// @retval true Enum.
/// @retval false Not enum.
///
bool CheckIfEnumValidation (
	const char *szTokensString,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool *pbIsError = NULL,
	bool bFlagsOperation = false,
	bool bIgnoreCommands = false
	);

///
/// @brief Get more information about the validation string.
///
/// This method parse the given validation string to find some validation rules.
///
/// @param[in] szTokensString String filled with tokens.
/// @param[out] ullMinValue will be filled with the minimum value (for integer).
/// @param[out] ullMaxValue will be filled with the maximum value (for integer).
/// @param[out] uiMinSize will be filled with the minimum size in characters (for string).
/// @param[out] uiMaxSize  will be filled with the maximum size in characters (for string).
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[out] pbIsError If this parameter is not equal to NULL then it will be true on error.
/// @param[in] bFlagsOperation If this parameter is true then the token string is represending a mask flags list.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
/// @retval true The validation string is of an enum.
/// @retval false The validation string is not of an enum.
///
bool GetValidationInfo (
	const char *szTokensString,
	bs_uint64& ullMinValue,
	bs_uint64& ullMaxValue,
	unsigned int& uiMinSize,
	unsigned int& uiMaxSize,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool *pbIsError = NULL,
	bool bFlagsOperation = false,
	bool bIgnoreCommands = false
	);

///
/// @brief Create a string filled with the list of allowed values.
///
/// This method can be used to export part of the validation features 
/// to another validation format.
///
/// @param[in] szTokensString String filled with tokens.
/// @param[out] oOutString Will be filled with the output string.
/// @param[in] cOutSeparatorChar The separator character to use on the output string.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
///
void BuildStringListFromvalidation (
	const char *szTokensString,
	std::string& oOutString,
	char cOutSeparatorChar,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool bIgnoreCommands = false
	);

///
/// @brief Get a value from list of values string.
///
/// This method extract the first value from the given list string. 
/// The ppNextValue parameter will be filled with a position after 
/// the first parameter. The only use for the pointer filled on 
/// ppNextValue is for calling to this method again to get the 
/// next parameter.
///
/// @param[in] szList Pointer to a list of values.
/// @param[out] oTypeOut Will be filled with the type of the first parameter been found.
/// @param[out] oNameOut Will be filled with the name of the first parameter been found.
/// @param[out] oValueOut Will be filled with the value of the first parameter been found.
/// @param[out] ppNextValue If this parameter is not equal to NULL then it'll be filled with a pointer to after the first value on the list string.
/// @retval true A value string been found.
/// @retval false A value string not been found.
///
bool GetValueFromList (
	const char *szList,
	std::string& oTypeOut,
	std::string& oNameOut,
	std::string& oValueOut,
	const char **ppNextValue
	);

///
/// @brief Extract command's value.
///
/// This method find and extract a command's value from the given list string.
///
/// @param[in] szTokensString Pointer to a list of values.
/// @param[in] szCommandName The command to find.
/// @param[out] uiSizeOfValue Will be filled with the command's value.
/// @param[out] ppNamePos Will be filled with the start of the real command name.
/// @param[out] uiNameSize The size in characters of the real command name.
/// @param[in] uiSizeOfTokensString The size of the complete tokens string. This parameter can be equal to -1 to auto detect the real size.
/// @param[in] cSeparatorChar The character that separaring between tokens.
/// @param[in] cTokenValueChar Can be used for tokens following a value to declare the separator character between the token name and the token value. To disable this feature this parameter must be equal to the cSeparatorChar parameter.
/// @param[in] bIgnoreCommands If this parameter is true then all the name strings that starting with '@' will be ignored.
/// @retval NULL Command not found.
/// @retval else Pointer to the command's value.
///
const char *LocateCmdOnList (
	const char *szTokensString,
	const char *szCommandName,
	unsigned int& uiSizeOfValue,
	const char **ppNamePos,
	unsigned int& uiNameSize,
	unsigned int uiSizeOfTokensString = (unsigned int) -1,
	char cSeparatorChar = ';',
	char cTokenValueChar = '=',
	bool bIgnoreCommands = false
	);

///
/// @brief Generic language for describing a value string with macros.
///
/// This method is doing the generic parsing part of a value string filled with 
/// macro declaration. This method is parsing automatic any of the generic macros 
/// but the calling module must parse any of the non-generic macros.
///
/// @param[in] szInput Input string.
/// @param[out] oOutValue Any output data will be appended to this string.
/// @param[in] uiSizeOfInput The size of the input string. This parameter can be equal to -1 to auto detect the string size.
/// @param[out] uiNextMacroNamePos Will be filled with the position to the macro's name. 
/// @param[out] uiNextMacroNameSize Will be filled with the size of the macro's name.
/// @param[out] uiNextMacroValAPos Will be filled with the position to the macro's first parameter.
/// @param[out] uiNextMacroValASize Will be filled with the size of the macro's first parameter.
/// @param[out] uiNextMacroValBPos Will be filled with the position to the macro's second parameter.
/// @param[out] uiNextMacroValBSize Will be filled with the size of the macro's second parameter.
/// @param[out] uiNewSizeOfInput Will be filled with the new size of the input string (for getting more characters).
/// @param[out] bIsError Will be true in case of an error.
/// @retval NULL Either error or no more characters left to parse.
/// @retval else Pointer to the next characters to parse.
///
const char *ValueLangMiniParser (
	const char *szInput,
	std::string& oOutValue,
	unsigned int uiSizeOfInput,
	unsigned int& uiNextMacroNamePos,
	unsigned int& uiNextMacroNameSize,
	unsigned int& uiNextMacroValAPos,
	unsigned int& uiNextMacroValASize,
	unsigned int& uiNextMacroValBPos,
	unsigned int& uiNextMacroValBSize,
	unsigned int& uiNewSizeOfInput,
	bool& bIsError
	);

///
/// @brief Translate IP address string into real IP address data.
///
/// This method extract IP address from the given string.
///
/// @param[in] szInput Input string.
/// @param[in] uiSizeOfInput Size of the input string in characters. This parameter can be equal to -1 to auto dectect the string's size.
/// @param[out] pbIsError If this parameter is not equal to NULL then it'll be true if the input string has invalid IP format.
/// @return The IP address as a number.
///
unsigned long TranslateToIp (
	const char *szInput,
	unsigned int uiSizeOfInput = (unsigned int) -1,
	bool *pbIsError = NULL
	);

///
/// @brief Create IP address string.
///
/// This method create IP address string from the given value.
///
/// @param[in] dwIpAddress The IP address as a number.
/// @param[out] oIpString Will be filled with the IP address as a string.
/// @retval true Operation succeeded.
/// @retval false Operation failed.
///
bool CreateIpString (
	unsigned long dwIpAddress,
	std::string& oIpString
	);

///
/// @brief Convert binary data into a hex dump string.
///
/// This method convert up to 16 bytes of data into a hex string that you can display.
///
/// @param[in] pData The data to convert.
/// @param[out] szHexLine Buffer to hold the generated line. The buffer size must be at last 66 bytes.
/// @param[in] uiDataSize The size of the data to convert. This method will covert up to 16 bytes.
///
void BinToHexLine(
	const unsigned char *pData,
	char *szHexLine,
	unsigned int uiDataSize
	);

#endif // H_STRING_PARSER_HEAD

//
// End of the header file string_parser.h
//

