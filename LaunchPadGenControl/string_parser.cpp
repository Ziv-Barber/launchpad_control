
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
/// @brief Ziv Barber string parsing functions (implementation).
///
/// This is the implementation of all the Ziv Barber string parsing functions.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_parser.h"

//
// Some internal definess:
//

//
// Private prototypes:
//

//
// Global variables:
//

static const char g_szBooleanNames[] = "false=0;true=1;no=0;yes=1;disable*=0;enable*=1;off=0;on=1;reset=0;set=1"; ///< Declaration of a boolean expression.

//
// Public code:
//

int ExtendedCompare (
	char *pInputString,
	char *pTokensString,
	int iSizeOfInputString,
	int iSizeOfTokenString,
	bool bFindOperation,
	bool bInsensitive,
	bool bIgnoreWhitespace,
	bool bIsTokensOperation,
	bool bEnableWildcard,
	char cSeparatorChar,
	char cTokenValueChar,
	int *piOffsetToValue,
	int *piValueSize,
	int *piOffsetToToken,
	int *piTokenSize
	)
{
	char *pCurIn;    // Current position on the input string.
	char *pCurToken; // Current position on the tokens string.
	char *pInBase;   // Current test start.
	int iCurIndex;   // Current token number.
	int iInStart;    // Offset of the first character match on the input string.
	int iCurInPos;   // Current position on the input string.
	int iTknStart;   // Offset of the first character match on the tokens string.
	int iCurTknPos;  // Current position on the tokens string.
	int iInType;     // Status of the last character read operation from the input string.
	int iTokenType;  // Status of the last character read operation from the tokens string.
	char cCurIn;     // Current character from the input string.
	char cCurToken;  // Current character from the tokens string.

	// Initialize the local variables:
	pCurIn = pInputString;
	pCurToken = pTokensString;
	pInBase = pInputString;
	iInStart = 0;
	iTknStart = 0;
	iCurInPos = 0;
	iCurTknPos = 0;

	// Initialize the output parameters:
	iCurIndex = 0;
	if ( piOffsetToValue != NULL )
	{
		(*piOffsetToValue) = 0;
	} // Endif.
	if ( piValueSize != NULL )
	{
		(*piValueSize) = 0;
	} // Endif.
	if ( piOffsetToToken != NULL )
	{
		(*piOffsetToToken) = 0;
	} // Endif.
	if ( piTokenSize != NULL )
	{
		(*piTokenSize) = 0;
	} // Endif.

	// We must have a token string:
	if ( pCurToken == NULL )
	{
		// Nice way to test if a string is empty:
		if ( pInputString == NULL )
		{
			return 0;

		} else if ( iSizeOfInputString == 0 )
		{
			return 0;

		} else if ( (iSizeOfInputString < 0) && ((*pInputString) == 0) )
		{
			return 0;

		} else
		{
			return -1;
		} // Endif.

	} else if ( iSizeOfTokenString == 0 )
	{
		// Nice way to test if a string is empty:
		if ( pInputString == NULL )
		{
			return 0;

		} else if ( iSizeOfInputString == 0 )
		{
			return 0;

		} else if ( (iSizeOfInputString < 0) && ((*pInputString) == 0) )
		{
			return 0;

		} else
		{
			return -1;
		} // Endif.

	} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
	{
		// Nice way to test if a string is empty:
		if ( pInputString == NULL )
		{
			return 0;

		} else if ( iSizeOfInputString == 0 )
		{
			return 0;

		} else if ( (iSizeOfInputString < 0) && ((*pInputString) == 0) )
		{
			return 0;

		} else
		{
			return -1;
		} // Endif.
	} // Endif.

	// Loop to do the compare:
	do
	{
		// Get the next character from the input string:
		iInType = 1;
		while ( iInType == 1 )
		{
			// End of the input string:
			if ( pCurIn == NULL )
			{
				iInType = 3; // End signal.
				cCurIn = 0;

			// End of the input string:
			} else if ( (iSizeOfInputString >= 0) && (iCurInPos >= iSizeOfInputString) )
			{
				iInType = 3; // End signal.
				cCurIn = 0;

			// End of the input string:
			} else if ( (iSizeOfInputString < 0) && ((*pCurIn) == 0) )
			{
				iInType = 3; // End signal.
				cCurIn = 0;

			// Normal character:
			} else
			{
				iInType = 0; // Normal.
				cCurIn = (*pCurIn);

				// Insensitive mode:
				if ( bInsensitive == true )
				{
					if ( (cCurIn >= 0x41) && (cCurIn < 0x5A) )
					{
						cCurIn += 0x20;
					} // Endif.
				} // Endif.

				// Ignore whitespace mode:
				if ( bIgnoreWhitespace == true )
				{
					if ( (cCurIn == 0) || (cCurIn == 9) || (cCurIn == 0xA) || (cCurIn == 0xD) || (cCurIn == ' ') )
					{
						cCurIn = ' ';
						if ( iCurInPos == iInStart )
						{
							iInType = 1; // Ignore.
						} // Endif.

						// Skeep all the whitespace characters:
						while ( cCurIn == ' ' )
						{
							iCurInPos++;
							pCurIn++;
							if ( (iSizeOfInputString >= 0) && (iCurInPos >= iSizeOfInputString) )
							{
								iInType = 3; // End signal.
								cCurIn = 0;
								break;

							} else if ( (iSizeOfInputString < 0) && ((*pCurIn) == 0) )
							{
								iInType = 3; // End signal.
								cCurIn = 0;
								break;

							} else if ( ((*pCurIn) != 0) && ((*pCurIn) != 9) && ((*pCurIn) != 0xA) && ((*pCurIn) != 0xD) && ((*pCurIn) != ' ') )
							{
								if ( iInType != 1 )
								{
									iCurInPos--;
									pCurIn--;
								} // Endif.
								break;
							} // Endif.
						} // End of while loop.
					} // Endif.
				} // Endif.
			} // End of while loop.
		} // Endif - end of getting character from the input string.

		// Get the next character from the tokens string:
		iTokenType = 1;
		while ( iTokenType == 1 )
		{
			// End of the tokens string:
			if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
			{
				iTokenType = 3; // End signal.
				cCurToken = 0;

			// End of the tokens string:
			} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
			{
				iTokenType = 3; // End signal.
				cCurToken = 0;

			// Token end:
			} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
			{
				iTokenType = 4; // End of token.
				cCurToken = 0;

			// Token's value:
			} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cTokenValueChar) )
			{
				iTokenType = 2; // End of token's name.
				cCurToken = 0;

			// Normal character:
			} else
			{
				iTokenType = 0; // Normal.
				cCurToken = (*pCurToken);

				// Insensitive mode:
				if ( bInsensitive == true )
				{
					if ( (cCurToken >= 0x41) && (cCurToken < 0x5A) )
					{
						cCurToken += 0x20;
					} // Endif.
				} // Endif.

				// Ignore whitespace mode:
				if ( bIgnoreWhitespace == true )
				{
					if ( (cCurToken == 0) || (cCurToken == 9) || (cCurToken == 0xA) || (cCurToken == 0xD) || (cCurToken == ' ') )
					{
						cCurToken = ' ';
						if ( iCurTknPos == iTknStart )
						{
							iTokenType = 1; // Ignore.
						} // Endif.

						// Skeep all the whitespace characters:
						while ( cCurToken == ' ' )
						{
							iCurTknPos++;
							pCurToken++;
							if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
							{
								iTokenType = 3; // End signal.
								cCurToken = 0;
								break;

							} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
							{
								iTokenType = 3; // End signal.
								cCurToken = 0;
								break;

							// Token end:
							} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
							{
								iTokenType = 4; // End of token.
								cCurToken = 0;
								break;

							// Token's value:
							} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cTokenValueChar) )
							{
								iTokenType = 2; // End of token's name.
								cCurToken = 0;
								break;

							} else if ( ((*pCurToken) != 0) && ((*pCurToken) != 9) && ((*pCurToken) != 0xA) && ((*pCurToken) != 0xD) && ((*pCurToken) != ' ') )
							{
								if ( iTokenType != 1 )
								{
									iCurTknPos--;
									pCurToken--;
								} // Endif.
								break;
							} // Endif.
						} // End of while loop.
					} // Endif.
				} // Endif.

				// Wildcards simple tricks:
				if ( bEnableWildcard == true )
				{
					if ( cCurToken == '\\' )
					{
						iCurTknPos++;
						pCurToken++;
						if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
						{
							iTokenType = 3; // End signal.
							cCurToken = 0;

						} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
						{
							iTokenType = 3; // End signal.
							cCurToken = 0;

						// Token end:
						} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
						{
							iTokenType = 4; // End of token.
							cCurToken = 0;

						// Token's value:
						} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cTokenValueChar) )
						{
							iTokenType = 2; // End of token's name.
							cCurToken = 0;

						} else
						{
							cCurToken = (*pCurToken);
						} // Endif.

					} else if ( cCurToken == '?' )
					{
						cCurToken = cCurIn;

					} else if ( cCurToken == '*' )
					{
						if ( iInType < 2 )
						{
							iInType = 3; // End signal.
							cCurIn = 0;
							while ( cCurIn == 0 )
							{
								iCurInPos++;
								pCurIn++;
								if ( (iSizeOfInputString >= 0) && (iCurInPos >= iSizeOfInputString) )
								{
									break;

								} else if ( (iSizeOfInputString < 0) && ((*pCurIn) == 0) )
								{
									break;
								} // Endif.
							} // End of while loop.
						} // Endif.

						iCurTknPos++;
						pCurToken++;
						if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
						{
							iTokenType = 3; // End signal.
							cCurToken = 0;

						} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
						{
							iTokenType = 3; // End signal.
							cCurToken = 0;

						// Token end:
						} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
						{
							iTokenType = 4; // End of token.
							cCurToken = 0;

						// Token's value:
						} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cTokenValueChar) )
						{
							iTokenType = 2; // End of token's name.
							cCurToken = 0;

						} else
						{
							cCurToken = (*pCurToken);
						} // Endif.
					} // Endif.
				} // Endif.
			} // End of while loop.
		} // Endif - end of getting character from the tokens string.

		// On find we don't need that the input string will be the same as the token:
		if ( (iTokenType > 1) && (bFindOperation == true) )
		{
			// Fake the end of the string:
			iInType = 3;
		} // Endif.

		// End of compare - both the same:
		if ( (iInType > 1) && (iTokenType > 1) )
		{
			if ( piOffsetToToken != NULL )
			{
				(*piOffsetToToken) = iTknStart;
			} // Endif.
			if ( piTokenSize != NULL )
			{
				(*piTokenSize) = (iCurTknPos - iTknStart);
			} // Endif.

			// Check if we need to fill also the token's value:
			if ( iTokenType == 2 )
			{
				// Find the size of the value string:
				iCurTknPos++;
				pCurToken++;
				iTknStart = iCurTknPos;
				iTokenType = 0;
				while ( iTokenType == 0 )
				{
					if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
					{
						iTokenType = 3; // End signal.

					} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
					{
						iTokenType = 3; // End signal.

					// Token end:
					} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
					{
						iTokenType = 4; // End of token.

					// Check if we need to ignore whitespace:
					} else if ( bIgnoreWhitespace == true )
					{
						// Skeep white space:
						if ( ((*pCurToken) == 0) || ((*pCurToken) == 9) || ((*pCurToken) == 0xA) || ((*pCurToken) == 0xD) || ((*pCurToken) == ' ') )
						{
							// The while loop goal is to not count any whitespace at the end of the value string:
							iCurInPos = iCurTknPos;
							pCurIn = pCurToken;
							while ( iTokenType == 0 )
							{
								if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
								{
									iTokenType = 3; // End signal.
									iCurTknPos = iCurInPos;
									pCurToken = pCurIn;
									break;

								} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
								{
									iTokenType = 3; // End signal.
									iCurTknPos = iCurInPos;
									pCurToken = pCurIn;
									break;

								// Token end:
								} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
								{
									iTokenType = 4; // End of token.
									iCurTknPos = iCurInPos;
									pCurToken = pCurIn;
									break;

								} else if ( ((*pCurToken) != 0) && ((*pCurToken) != 9) && ((*pCurToken) != 0xA) && ((*pCurToken) != 0xD) && ((*pCurToken) != ' ') )
								{
									break;

								} else
								{
									// The following condition take out any leading whitespace before the value itself:
									if ( iTknStart == iCurTknPos )
									{
										iTknStart++;
									} // Endif.

									iCurTknPos++;
									pCurToken++;
								} // Endif
							} // End of while loop.

						} else
						{
							iCurTknPos++;
							pCurToken++;
						} // Endif.

					} else
					{
						iCurTknPos++;
						pCurToken++;
					} // Endif
				} // End of while loop.

				// Check if we have a real value:
				if ( iCurTknPos > iTknStart )
				{
					if ( piOffsetToValue != NULL )
					{
						(*piOffsetToValue) = iTknStart;
					} // Endif.
					if ( piValueSize != NULL )
					{
						(*piValueSize) = (iCurTknPos - iTknStart);
					} // Endif.
				} // Endif.
			} // Endif.

			// Exit from the big loop:
			break;

		// Compare failed:
		} else if ( (iTokenType > 1) || (iInType > 1) || (cCurIn != cCurToken) )
		{
			// Go back to the current testing start on the input string:
			iCurInPos = iInStart;
			pCurIn = pInBase;

			// Locate the end of the token:
			if ( iTokenType < 2 )
			{
				iCurTknPos++;
				pCurToken++;
				while ( iTokenType < 2 )
				{
					if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
					{
						iTokenType = 3; // End signal.

					} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
					{
						iTokenType = 3; // End signal.

					// Token end:
					} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
					{
						iTokenType = 4; // End of token.

					// Token's value:
					} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cTokenValueChar) )
					{
						iTokenType = 2; // End of token's name.

					} else
					{
						iCurTknPos++;
						pCurToken++;
					} // Endif
				} // End of while loop.
			} // Endif.

			// Skeep the token's value (if exist):
			if ( iTokenType == 2 )
			{
				iCurTknPos++;
				pCurToken++;
				while ( iTokenType == 2 )
				{
					if ( (iSizeOfTokenString >= 0) && (iCurTknPos >= iSizeOfTokenString) )
					{
						iTokenType = 3; // End signal.

					} else if ( (iSizeOfTokenString < 0) && ((*pCurToken) == 0) )
					{
						iTokenType = 3; // End signal.

					// Token end:
					} else if ( (bIsTokensOperation == true) && ((*pCurToken) == cSeparatorChar) )
					{
						iTokenType = 4; // End of token.

					} else
					{
						iCurTknPos++;
						pCurToken++;
					} // Endif
				} // End of while loop.
			} // Endif.

			// End of token:
			if ( iTokenType == 4 )
			{
				// Prepare to test the next token if match:
				iCurTknPos++;
				pCurToken++;
				iTknStart = iCurTknPos;
				iCurIndex++;

			// End of all the tokens string:
			} else if ( iTokenType == 3 )
			{
				// Prepare to start working on all the tokens again:
				pCurToken = pTokensString;
				iTknStart = 0;
				iCurTknPos = 0;

				// On comapre operation we'll exit now:
				if ( bFindOperation == false )
				{
					if ( piOffsetToValue != NULL )
					{
						iCurIndex++;
						(*piOffsetToValue) = iCurIndex;
					} // Endif.
					iCurIndex = -1;

				// Move the base position:
				} else
				{
					iInStart++;
					pInBase++;
					iCurInPos++;
					pCurIn++;
					if ( (iSizeOfInputString >= 0) && (iCurInPos >= iSizeOfInputString) )
					{
						if ( piOffsetToValue != NULL )
						{
							iCurIndex++;
							(*piOffsetToValue) = iCurIndex;
						} // Endif.
						iCurIndex = -1;

					} else if ( (iSizeOfInputString < 0) && ((*pCurIn) == 0) )
					{
						if ( piOffsetToValue != NULL )
						{
							iCurIndex++;
							(*piOffsetToValue) = iCurIndex;
						} // Endif.
						iCurIndex = -1;
					} // Endif.
				} // Endif.
			} // Endif.

		// Move to the next characters:
		} else
		{
			iCurInPos++;
			pCurIn++;
			iCurTknPos++;
			pCurToken++;
		} // Endif.
	} while ( iCurIndex != -1 );

	// Return what we found:
	return iCurIndex;
}

bool GetBooleanAsString (
	char *szValue,
	int iSizeOfString
	)
{
	bs_uint64 ullValue; // The value as a number.
	int iRes;                // Returned value.

	// Crash protection:
	if ( szValue == NULL )
	{
		// It's like false:
		return false;
	} // Endif.

	// Call to the big compare function to do the real job:
	iRes = ExtendedCompare ( szValue, (char *) g_szBooleanNames, iSizeOfString, -1, false, true, true, true, true );

	// Try to parse it as a number:
	if ( iRes == -1 )
	{
		ullValue = DecodeNumber ( szValue, 0 );
		return ullValue == 0L ? false : true;
	} // Endif.

	// Return what we found:
	return (iRes & 1) == 1 ? true : false;
}

bs_uint64 DecodeNumber (
	const char *szInput,
	int iBase,
	int iStopHere,
	const char **pNext
	)
{
	char *pCur = (char *) szInput;                     // Next character to work on it.
	int iCharactersCount = 0;                          // How much characters parsed so far.
	bs_uint64 iNumber = 0;                        // Number found.
	bs_uint64 iDigitFound;                        // Digit found.
	bs_uint64 iRealBase = (bs_uint64) iBase; // Real base to use.
	char cMaxChar = 0;                                 // Maximum character for base above decimal.

	// Auto-detect base:
	if ( iBase == 0 )
	{
		// Octal, hex or binary:
		if ( (*pCur) == '0' )
		{
			iRealBase = 8;
			pCur++;
			iCharactersCount++;
			if ( iStopHere != 1 )
			{
				// Hex:
				if ( ((*pCur) == 'x') || ((*pCur) == 'X') )
				{
					iRealBase = 16;
					pCur++;
					iCharactersCount++;

				// Binary:
				} else if ( ((*pCur) == 'b') || ((*pCur) == 'B') )
				{
					iRealBase = 16;
					pCur++;
					iCharactersCount++;
				} // Endif.
			} // Endif.

		// Must be decimal:
		} else
		{
			iRealBase = 10;
		} // Endif.
	} // Endif.

	// Calculate the maximum character for base above decimal:
	if ( iRealBase > 10 )
	{
		cMaxChar = (char) iRealBase;
		cMaxChar -= 10;
		cMaxChar += 0x41;
		if ( cMaxChar > 0x5A )
		{
			cMaxChar = 0x5A;
		} // Endif.
	} // Endif.

	// Work on all the characters:
	do
	{
		// Another break test:
		if ( (iStopHere != 0) && (iCharactersCount == iStopHere) )
		{
			break;
		} // Endif.

		// 0 to 9:
		if ( ((*pCur) >= 0x30) && ((*pCur) <= 0x39) )
		{
			iDigitFound = (bs_uint64) (*pCur);
			iDigitFound -= 0x30;

		// Case letter:
		} else if ( (cMaxChar > 0) && ((*pCur) >= 0x41) && ((*pCur) <= cMaxChar) )
		{
			iDigitFound = (bs_uint64) (*pCur);
			iDigitFound -= 0x41;
			iDigitFound += 10;

		// No-case letter:
		} else if ( (cMaxChar > 0) && ((*pCur) >= 0x61) && ((*pCur) <= (0x20 + cMaxChar)) )
		{
			iDigitFound = (bs_uint64) (*pCur);
			iDigitFound -= 0x61;
			iDigitFound += 10;

		// Unknown character:
		} else
		{
			break;
		} // Endif.

		// Do some calculations:
		iNumber *= iRealBase;
		iNumber += iDigitFound;

		// Move to test the next character:
		pCur++;
		iCharactersCount++;
	} while ( iCharactersCount != iStopHere );

	// Save the last character if needed:
	if ( pNext != NULL )
	{
		(*pNext) = pCur;
	} // Endif.

	// Return the number found:
	return ( iNumber );
}

void EncodeNumber (
	char *szOutput,
	int iSizeOfBuffer,
	int iBase,
	bs_uint64 iNumber,
	bool bPrefix,
	bool bCase
	)
{
	char *pCur = szOutput;                // Current position to write the next character.
	char *pFirst;                         // First digit position.
	int iCharactersCount = 0;             // How much characters saved so far.
	bs_uint64 iRealNumber = iNumber; // Number found.
	bs_uint64 iDigit;                // Single digit to write.

	// Write the prefix if needed:
	if ( bPrefix != false )
	{
		if ( (iBase == 2) || (iBase == 8) || (iBase == 16) )
		{
			(*pCur) = '0';
			pCur++;
			iCharactersCount++;
			if ( (iCharactersCount + 1) == iSizeOfBuffer )
			{
				(*pCur) = 0;
				return;
			} // Endif.

			// Binary:
			if ( iBase == 2 )
			{
				(*pCur) = 'b';
				pCur++;
				iCharactersCount++;
				if ( (iCharactersCount + 1) == iSizeOfBuffer )
				{
					(*pCur) = 0;
					return;
				} // Endif.
			} // endif.

			// Hex:
			if ( iBase == 16 )
			{
				(*pCur) = 'x';
				pCur++;
				iCharactersCount++;
				if ( (iCharactersCount + 1) == iSizeOfBuffer )
				{
					(*pCur) = 0;
					return;
				} // Endif.
			} // endif.
		} // Endif.
	} // endif.

	// Move to the end of the string:
	pFirst = pCur;
	pCur = szOutput + iSizeOfBuffer - 1;
	(*pCur) = 0;
	if ( iNumber == 0 )
	{
		(*pFirst) = '0';
		pFirst++;
		(*pFirst) = 0;
		return;
	} // Endif.

	// Loop to create all the digits:
	while ( pFirst != pCur )
	{
		// Don't write 0:
		if ( iRealNumber == 0 )
		{
			break;
		} // Endif.

		// Get the next digit:
		pCur--;
		iDigit = (iRealNumber % (bs_uint64) (iBase));
		iRealNumber /= (bs_uint64) (iBase);
		if ( iDigit > 9 )
		{
			iDigit += 7;
			if ( bCase == false )
			{
				iDigit += 0x20;
			} // Endif.
		} // Endif.

		// Write the next digit:
		iDigit += 0x30;
		(*pCur) = (char) iDigit;
	} // End of while loop.

	// Loop to copy the number to the start of the string:
	if ( pFirst != pCur )
	{
		while ( (*pCur) != 0 )
		{
			(*pFirst) = (*pCur);
			pFirst++;
			pCur++;
		} // End of while loop.

		(*pFirst) = 0;
	} // Endif.
}

const char *FindUpToCharacter (
	const char *szValue,
	const char *szCharsList,
	std::string& oOutValue,
	unsigned int uiValueSize,
	unsigned int uiCharsSize
	)
{
	const char *pCurIn;        // Current input position.
	const char *pValStart;     // Start of the value been found.
	const char *pCurCIn;       // Current character to check.
	size_t uiCurVInPos;  // Input position.
	size_t uiCurVOutPos; // Output position.
	size_t uiCurCInPos;  // Characters position.
	bool bIsBreak;             // Will be true to break out of the loop.

	// Check for errors:
	oOutValue = "";
	if ( (szValue == NULL) || (szCharsList == NULL) || (uiValueSize == 0) || (uiCharsSize == 0) )
	{
		// Error:
		return NULL;
	} // Endif.

	// Loop on all the characters:
	pCurIn = szValue;
	pValStart = NULL;
	uiCurVInPos = 0;
	uiCurVOutPos = 0;
	bIsBreak = false;
	while ( bIsBreak == false )
	{
		// Loop on all the characters to check:
		pCurCIn = szCharsList;
		uiCurCInPos = 0;
		while ( bIsBreak == false )
		{
			if ( (*pCurCIn) == (*pCurIn) )
			{
				bIsBreak = true;
				break;
			} // Endif.

			// Find the next character:
			pCurCIn++;
			uiCurCInPos++;
			if ( (uiCharsSize == (unsigned int) -1) && ((*pCurCIn) == 0) )
			{
				break;

			} else if ( uiCharsSize <= uiCurCInPos )
			{
				break;
			} // Endif.
		} // End of while loop.

		// Check if we need to break;
		if ( bIsBreak == true )
		{
			break;
		} // Endif.

		// Check if we need to add this character to the output value:
		if ( ((*pCurIn) != ' ') && ((*pCurIn) != '\t') && ((*pCurIn) != '\n') && ((*pCurIn) != '\r') && ((*pCurIn) != 0) )
		{
			if ( pValStart == NULL )
			{
				pValStart = pCurIn;

			} else
			{
				uiCurVOutPos = (pCurIn - pValStart) + 1;
			} // Endif.
		} // Endif.

		// Find the next character:
		pCurIn++;
		uiCurVInPos++;
		if ( (uiValueSize == (unsigned int) -1) && ((*pCurIn) == 0) )
		{
			pCurIn = NULL;
			break;

		} else if ( uiValueSize <= uiCurVInPos )
		{
			pCurIn = NULL;
			break;
		} // Endif.
	} // End of while loop.

	// Check if we have an output value:
	if ( (pValStart != NULL) && (uiCurVOutPos > 0) )
	{
		oOutValue.append ( pValStart, uiCurVOutPos );
	} // Endif.

	// Return the position of the character been found:
	return pCurIn;
}

unsigned int GetTokenInfo (
	const char *szTokensString,
	unsigned int uiSizeOfTokensString,
	unsigned int *puiDataPos,
	unsigned int *puiDataSize,
	char cSeparatorChar,
	char cTokenValueChar
	)
{
	size_t uiRealSizeOfTokensString; // Real tokens string size.
	size_t uiCurPos;                 // Current position.
	size_t uiTokenDataPos;           // Token data start position.

	// Initialize the output parameters:
	if ( puiDataPos != NULL )
	{
		(*puiDataPos) = (unsigned int) -1;
	} // Endif.
	if ( puiDataSize != NULL )
	{
		(*puiDataSize) = 0;
	} // Endif.

	// Check for errors:
	if ( szTokensString == NULL )
	{
		// No tokens (well... no string):
		return (unsigned int) -1;
	} // Endif.

	// Auto detect the real size:
	uiRealSizeOfTokensString = uiSizeOfTokensString;
	if ( uiSizeOfTokensString == (unsigned int) -1 )
	{
		uiRealSizeOfTokensString = strlen ( szTokensString );
	} // Endif.

	// Initialize any other local variable:
	uiTokenDataPos = (unsigned int) -1;
	uiCurPos = 0;

	// Work on all the characters:
	for ( uiCurPos = 0; uiCurPos < uiRealSizeOfTokensString; uiCurPos++ )
	{
		if ( szTokensString[uiCurPos] == cSeparatorChar )
		{
			break;
		} // Endif.

		if ( (szTokensString[uiCurPos] == cTokenValueChar) && (uiTokenDataPos == (unsigned int) -1) )
		{
			if ( uiCurPos == 0 )
			{
				// Error:
				return (unsigned int) -1;
			} // Endif.

			uiTokenDataPos = uiCurPos + 1;
		} // Endif.
	} // End of for loop.

	// Check if there's no data:
	if ( uiTokenDataPos == (unsigned int) -1 )
	{
		// The current position is the same as the size of the token name:
		return uiCurPos == 0 ? (unsigned int) -1 : uiCurPos;
	} // Endif.

	// Do some calculations:
	if ( uiCurPos != uiTokenDataPos )
	{
		if ( puiDataPos != NULL )
		{
			(*puiDataPos) = uiTokenDataPos;
		} // Endif.
		if ( puiDataSize != NULL )
		{
			(*puiDataSize) = (uiCurPos - uiTokenDataPos);
		} // Endif.
	} // Endif.
	return (uiTokenDataPos - 1);
}

unsigned int GetSizeOfWhiteSpace (
	const char *szText,
	unsigned int uiStrSize,
	unsigned int& uiTextSize
	)
{
	unsigned int uiStartPos;     // The real start of the text.
	unsigned int uiTextFullSize; // The full real size of the input string.
	unsigned int uiCurPos;       // Current position.

	// Check for errors:
	if ( (szText == NULL) || (uiStrSize == 0) )
	{
		// Error:
		uiTextSize = 0;
		return (unsigned int) -1;
	} // Endif.

	// Initialize the output parameters:
	uiStartPos = (unsigned int) -1;
	uiTextSize = 0;
	uiTextFullSize = uiStrSize;
	if ( uiStrSize == (unsigned int) -1 )
	{
		uiTextFullSize = strlen ( szText );
	} // Endif.

	// Work on all the characters:
	for ( uiCurPos = 0; uiCurPos < uiTextFullSize; uiCurPos++ )
	{
		if ( ((*szText) != ' ') && ((*szText) != '\t') && ((*szText) != '\n') && ((*szText) != '\r') && ((*szText) != 0) )
		{
			if ( uiStartPos == (unsigned int) -1 )
			{
				uiStartPos = uiCurPos;
				uiTextSize = 1;

			} else
			{
				uiTextSize = ((uiCurPos - uiStartPos) + 1);
			} // Endif.
		} // End of for loop.
	} // End of for loop.

	// Return the start position:
	return uiStartPos;
}

bs_uint64 TranslateEnumToValue (
	const char *szEnumItem,
	const char *szTokensString,
	unsigned int uiSizeOfEnumItem,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool *pbIsError,
	bool bFlagsOperation,
	bool bIgnoreCommands
	)
{
	char *pCur;              // Current position on a string.
	int iDtPos;              // Data position.
	int iDtSize;             // Data size.
	int iEnumPos;            // ID of the enum item.
	int iLoopCount;          // Loop counter.
	unsigned int uiDtPos;    // Data position.
	unsigned int uiDtSize;   // Data size.
	unsigned int uiTknSize;  // The size of the enum item name.
	unsigned int uiCurPos;   // Current token.
	unsigned int uiRealSize; // The real size of the tokens string.
	bs_uint64 ullValue; // Value been found.

	// Initialize the output parameter:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = true;
	} // Endif.

	// Do some calculations:
	uiRealSize = uiSizeOfTokensString;
	if ( uiRealSize == (unsigned int) -1 )
	{
		uiRealSize = strlen ( szTokensString );
	} // Endif.

	// Locate this enum item:
	iEnumPos = ExtendedCompare ( (char *) szEnumItem, (char *) szTokensString, (int) uiSizeOfEnumItem, (int) uiRealSize, false, true, true, true, true, cSeparatorChar, cTokenValueChar, &iDtPos, &iDtSize );
	if ( iEnumPos < 0 )
	{
		// Not found:
		return 0;
	} // Endif.

	// Check if we have a value:
	if ( (iDtPos != -1) && (iDtSize > 0) )
	{
		pCur = (char *) szTokensString + iDtPos;
		while ( ((*pCur) == ' ') || ((*pCur) == '\t') )
		{
			pCur++;
		} // End of while loop.

		// Update that there're no errors:
		if ( pbIsError != NULL )
		{
			(*pbIsError) = false;
		} // Endif.

		return DecodeNumber ( pCur );
	} // Endif.

	// Initialize the local variables:
	uiCurPos = 0;
	if ( bFlagsOperation == true )
	{
		ullValue = 1;

	} else
	{
		ullValue = 0;
	} // Endif.

	// Loop on all the items:
	for ( iLoopCount = 0; iLoopCount <= iEnumPos; iLoopCount++ )
	{
		uiTknSize = GetTokenInfo ( szTokensString + uiCurPos, uiRealSize - uiCurPos, &uiDtPos, &uiDtSize, cSeparatorChar, cTokenValueChar );
		if ( uiTknSize == (unsigned int) -1 )
		{
			// Error:
			return 0;
		} // Endif.

		// Check if this is a command:
		if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@*", uiTknSize, -1, false, false, true, false, true ) == 0) )
		{
			// Skeep this one:

		} else
		{
			// Check if we have a value:
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				pCur = (char *) szTokensString + uiDtPos;
				while ( ((*pCur) == ' ') || ((*pCur) == '\t') )
				{
					pCur++;
				} // End of while loop.

				ullValue = DecodeNumber ( pCur );

			} else
			{
				if ( bFlagsOperation == true )
				{
					ullValue <<= 1;

				} else
				{
					ullValue++;
				} // Endif.
			} // Endif.
		} // Endif.

		if ( uiDtPos != (unsigned int) -1 )
		{
			uiCurPos += (uiDtPos + uiDtSize);

		} else
		{
			uiCurPos += uiTknSize;
		} // Endif.

		if ( ((uiRealSize - uiCurPos) > 0) && (szTokensString[uiCurPos] == cSeparatorChar) )
		{
			uiCurPos++;
		} // Endif.
	} // End of for loop.

	// Update that there're no errors:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = false;
	} // Endif.

	// Return the value been calculated:
	return ullValue;
}

const char *TranslateValueToName (
	bs_uint64 ullValue,
	const char *szTokensString,
	unsigned int& uiSizeOfName,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool *pbIsError,
	bool bFlagsOperation,
	bool bIgnoreCommands
	)
{
	char *pCur;                   // Current position on a string.
	int iLoopCount;               // Loop counter.
	unsigned int uiDtPos;         // Data position.
	unsigned int uiDtSize;        // Data size.
	unsigned int uiTknSize;       // The size of the enum item name.
	unsigned int uiCurPos;        // Current token.
	unsigned int uiRealSize;      // The real size of the tokens string.
	bs_uint64 ullFoundValue; // Value been found.

	// Initialize the output parameter:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = true;
	} // Endif.

	// Do some calculations:
	uiRealSize = uiSizeOfTokensString;
	if ( uiRealSize == (unsigned int) -1 )
	{
		uiRealSize = strlen ( szTokensString );
	} // Endif.

	// Initialize the local variables:
	uiSizeOfName = 0;
	uiCurPos = 0;
	if ( bFlagsOperation == true )
	{
		ullFoundValue = 1;

	} else
	{
		ullFoundValue = 0;
	} // Endif.

	// Loop on all the items:
	iLoopCount = 0;
	while ( iLoopCount >= 0 )
	{
		uiTknSize = GetTokenInfo ( szTokensString + uiCurPos, uiRealSize - uiCurPos, &uiDtPos, &uiDtSize, cSeparatorChar, cTokenValueChar );
		if ( uiTknSize == (unsigned int) -1 )
		{
			// Error:
			return NULL;
		} // Endif.

		// Check if this is a command:
		if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@*", uiTknSize, -1, false, false, true, false, true ) == 0) )
		{
			// Skeep this one:

		} else
		{
			// Check if we have a value:
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				pCur = (char *) szTokensString + uiCurPos + uiDtPos;
				while ( ((*pCur) == ' ') || ((*pCur) == '\t') )
				{
					pCur++;
				} // End of while loop.

				ullFoundValue = DecodeNumber ( pCur );

			} else
			{
				if ( bFlagsOperation == true )
				{
					ullFoundValue <<= 1;

				} else
				{
					ullFoundValue++;
				} // Endif.
			} // Endif.

			// Check if this is the requested value:
			if ( ullFoundValue == ullValue )
			{
				// We found it:
				ullValue = GetSizeOfWhiteSpace ( szTokensString + uiCurPos, uiTknSize, uiSizeOfName );
				if ( ullValue == (unsigned int) -1 )
				{
					// Error:
					return NULL;
				} // Endif.

				// Update that there're no errors:
				if ( pbIsError != NULL )
				{
					(*pbIsError) = false;
				} // Endif.

				// Return the name:
				return (szTokensString + uiCurPos + ullValue);
			} // Endif.
		} // Endif.

		if ( uiDtPos != (unsigned int) -1 )
		{
			uiCurPos += (uiDtPos + uiDtSize);

		} else
		{
			uiCurPos += uiTknSize;
		} // Endif.

		if ( ((uiRealSize - uiCurPos) > 0) && (szTokensString[uiCurPos] == cSeparatorChar) )
		{
			uiCurPos++;
		} // Endif.

		iLoopCount++;
	} // End of while loop.

	// Invalid name:
	return NULL;
}

bool CheckIfBooleanValidation (
	const char *szTokensString,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool *pbIsError,
	bool bFlagsOperation,
	bool bIgnoreCommands
	)
{
	char *pCur;                   // Current position on a string.
	int iLoopCount;               // Loop counter.
	unsigned int uiDtPos;         // Data position.
	unsigned int uiDtSize;        // Data size.
	unsigned int uiTknSize;       // The size of the enum item name.
	unsigned int uiCurPos;        // Current token.
	unsigned int uiRealSize;      // The real size of the tokens string.
	bs_uint64 ullFoundValue; // Value been found.
	bs_uint64 ullMinVal;     // Minimum value.
	bs_uint64 ullMaxVal;     // Maximum value.
	bs_uint64 ullCmdValue;   // The value of a validation command.
	bool bForceEnumOnly;          // Will be true if it's not allowed to enter values other then on the validation string.
	bool bAutoDetect;             // Auto-detect if normal values allowed.

	// Initialize the output parameter:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = true;
	} // Endif.

	// Do some calculations:
	uiRealSize = uiSizeOfTokensString;
	if ( uiRealSize == (unsigned int) -1 )
	{
		uiRealSize = strlen ( szTokensString );
	} // Endif.

	// Initialize the local variables:
	bForceEnumOnly = false;
	bAutoDetect = true;
	ullMinVal = 0;
	ullMaxVal = (unsigned int) -1;
	uiCurPos = 0;
	if ( bFlagsOperation == true )
	{
		ullFoundValue = 1;

	} else
	{
		ullFoundValue = 0;
	} // Endif.

	// Loop on all the validation rules:
	iLoopCount = 0;
	while ( iLoopCount >= 0 )
	{
		// Get information about the current validation instruction:
		uiTknSize = GetTokenInfo ( szTokensString + uiCurPos, uiRealSize - uiCurPos, &uiDtPos, &uiDtSize, cSeparatorChar, cTokenValueChar );
		if ( uiTknSize == (unsigned int) -1 )
		{
			// End of the tokens string:
			break;
		} // Endif.

		// Minimum command:
		if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@min", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				ullMinVal = DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
			} // Endif.

		// Maximum command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@max", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				ullMaxVal = DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
			} // Endif.

		// String minimum command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@size_min", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				ullCmdValue = DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
				if ( ullCmdValue > 1 )
				{
					// Update that there're no errors:
					if ( pbIsError != NULL )
					{
						(*pbIsError) = false;
					} // Endif.

					// Not boolean:
					return false;
				} // Endif.
			} // Endif.

		// String maximum command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@size_max", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				ullCmdValue = DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
				if ( ullCmdValue == 0 )
				{
					// Update that there're no errors:
					if ( pbIsError != NULL )
					{
						(*pbIsError) = false;
					} // Endif.

					// Not boolean:
					return false;
				} // Endif.
			} // Endif.

		// Allow normal values command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@enum_only", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				bAutoDetect = false;
				bForceEnumOnly = GetBooleanAsString ( (char *) (szTokensString + uiCurPos + uiDtPos), (int) uiDtSize );
			} // Endif.

		// Check if this is a command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@*", uiTknSize, -1, false, false, true, false, true ) == 0) )
		{
			// Skeep this one:

		} else
		{
			// Valid value declaration:
			if ( bAutoDetect == true )
			{
				bAutoDetect = false;
				bForceEnumOnly = true;
			} // Endif.

			// Check if we have a value:
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				pCur = (char *) szTokensString + uiCurPos + uiDtPos;
				while ( ((*pCur) == ' ') || ((*pCur) == '\t') )
				{
					pCur++;
				} // End of while loop.

				ullFoundValue = DecodeNumber ( pCur );

			} else
			{
				if ( bFlagsOperation == true )
				{
					ullFoundValue <<= 1;

				} else
				{
					ullFoundValue++;
				} // Endif.
			} // Endif.

			if ( ullFoundValue > 1 )
			{
				// Update that there're no errors:
				if ( pbIsError != NULL )
				{
					(*pbIsError) = false;
				} // Endif.

				// Not boolean:
				return false;
			} // Endif.
		} // Endif.

		// Move to the next validation rule:
		if ( uiDtPos != (unsigned int) -1 )
		{
			uiCurPos += (uiDtPos + uiDtSize);

		} else
		{
			uiCurPos += uiTknSize;
		} // Endif.
		if ( ((uiRealSize - uiCurPos) > 0) && (szTokensString[uiCurPos] == cSeparatorChar) )
		{
			uiCurPos++;
		} // Endif.

		iLoopCount++;
	} // End of while loop.

	// Update that there're no errors:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = false;
	} // Endif.

	// Check the minimum and maximum:
	if ( bForceEnumOnly == false )
	{
		if ( (ullMinVal != 0) || (ullMaxVal != 1) )
		{
			// Can't be boolean:
			return false;
		} // Endif.
	} // Endif.

	// That's all:
	return true;
}

bool CheckIfEnumValidation (
	const char *szTokensString,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool *pbIsError,
	bool bFlagsOperation,
	bool bIgnoreCommands
	)
{
	bs_uint64 ullMinValue; // Minimum value.
	bs_uint64 ullMaxValue; // Maximum value.
	unsigned int uiMinSize;     // Minimum size.
	unsigned int uiMaxSize;     // Maximum size.

	// Use the validation info function:
	return GetValidationInfo ( szTokensString, ullMinValue, ullMaxValue, uiMinSize, uiMaxSize, uiSizeOfTokensString, cSeparatorChar, cTokenValueChar, pbIsError, bFlagsOperation, bIgnoreCommands );
}

bool GetValidationInfo (
	const char *szTokensString,
	bs_uint64& ullMinValue,
	bs_uint64& ullMaxValue,
	unsigned int& uiMinSize,
	unsigned int& uiMaxSize,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool *pbIsError,
	bool bFlagsOperation,
	bool bIgnoreCommands
	)
{
	int iLoopCount;          // Loop counter.
	unsigned int uiDtPos;    // Data position.
	unsigned int uiDtSize;   // Data size.
	unsigned int uiTknSize;  // The size of the enum item name.
	unsigned int uiCurPos;   // Current token.
	unsigned int uiRealSize; // The real size of the tokens string.
	bool bForceEnumOnly;     // Will be true if it's not allowed to enter values other then on the validation string.
	bool bAutoDetect;        // Auto-detect if normal values allowed.

	// Initialize the output parameter:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = true;
	} // Endif.

	// Do some calculations:
	uiRealSize = uiSizeOfTokensString;
	if ( uiRealSize == (unsigned int) -1 )
	{
		uiRealSize = strlen ( szTokensString );
	} // Endif.

	// Initialize the local variables:
	bForceEnumOnly = false;
	bAutoDetect = true;
	ullMinValue = 0;
	ullMaxValue = (unsigned int) -1;
	uiCurPos = 0;

	// Loop on all the validation rules:
	iLoopCount = 0;
	while ( iLoopCount >= 0 )
	{
		// Get information about the current validation instruction:
		uiTknSize = GetTokenInfo ( szTokensString + uiCurPos, uiRealSize - uiCurPos, &uiDtPos, &uiDtSize, cSeparatorChar, cTokenValueChar );
		if ( uiTknSize == (unsigned int) -1 )
		{
			// End of the tokens string:
			break;
		} // Endif.

		// Minimum command:
		if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@min", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				ullMinValue = DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
			} // Endif.

		// Maximum command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@max", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				ullMaxValue = DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
			} // Endif.

		// String minimum command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@size_min", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				uiMinSize = (unsigned int) DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
			} // Endif.

		// String maximum command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@size_max", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				uiMaxSize = (unsigned int) DecodeNumber ( szTokensString + uiCurPos + uiDtPos, 0, (int) uiDtSize );
			} // Endif.

		// Enum only command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@enum_only", uiTknSize, -1, false, false, true ) == 0) )
		{
			if ( (uiDtPos != (unsigned int) -1) && (uiDtSize > 0) )
			{
				bAutoDetect = false;
				bForceEnumOnly = GetBooleanAsString ( (char *) (szTokensString + uiCurPos + uiDtPos), (int) uiDtSize );
			} // Endif.

		// Check if this is a command:
		} else if ( (bIgnoreCommands == true) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@*", uiTknSize, -1, false, false, true, false, true ) == 0) )
		{
			// Skeep this one:

		} else
		{
			// Valid value declaration:
			if ( bAutoDetect == true )
			{
				bAutoDetect = false;
				bForceEnumOnly = true;
			} // Endif.
		} // Endif.

		// Move to the next validation rule:
		if ( uiDtPos != (unsigned int) -1 )
		{
			uiCurPos += (uiDtPos + uiDtSize);

		} else
		{
			uiCurPos += uiTknSize;
		} // Endif.
		if ( ((uiRealSize - uiCurPos) > 0) && (szTokensString[uiCurPos] == cSeparatorChar) )
		{
			uiCurPos++;
		} // Endif.

		iLoopCount++;
	} // End of while loop.

	// Update that there're no errors:
	if ( pbIsError != NULL )
	{
		(*pbIsError) = false;
	} // Endif.

	// That's all:
	return bForceEnumOnly;
}

void BuildStringListFromvalidation (
	const char *szTokensString,
	std::string& oOutString,
	char cOutSeparatorChar,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool bIgnoreCommands
	)
{
	char szTemp[32];             // Temporary string.
	int iLoopCount;              // Loop counter.
	unsigned int uiDtPos;        // Data position.
	unsigned int uiDtSize;       // Data size.
	unsigned int uiTknSize;      // The size of the enum item name.
	unsigned int uiCurPos;       // Current token.
	unsigned int uiRealSize;     // The real size of the tokens string.
	unsigned int uiNameRealPos;  // Name real position.
	unsigned int uiNameRealSize; // Name real size.
	unsigned int uiItemsCount;   // Count of items been found.
	bool bForceEnumOnly;         // Will be true if it's not allowed to enter values other then on the validation string.
	bool bAutoDetect;            // Auto-detect if normal values allowed.

	// Do some calculations:
	uiRealSize = uiSizeOfTokensString;
	if ( uiRealSize == (unsigned int) -1 )
	{
		uiRealSize = strlen ( szTokensString );
	} // Endif.

	// Initialize the local variables:
	bForceEnumOnly = false;
	bAutoDetect = true;
	uiCurPos = 0;
	uiItemsCount = 0;
	oOutString = "";
	szTemp[0] = cOutSeparatorChar;
	szTemp[1] = 0;

	// Loop on all the validation rules:
	iLoopCount = 0;
	while ( iLoopCount >= 0 )
	{
		// Get information about the current validation instruction:
		uiTknSize = GetTokenInfo ( szTokensString + uiCurPos, uiRealSize - uiCurPos, &uiDtPos, &uiDtSize, cSeparatorChar, cTokenValueChar );
		if ( uiTknSize == (unsigned int) -1 )
		{
			// End of the tokens string:
			break;
		} // Endif.

		// Check if this is a command:
		if ( (bIgnoreCommands == false) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@*", uiTknSize, -1, false, false, true, false, true ) == 0) )
		{
			// Skeep this one:

		} else
		{
			// Valid value declaration:
			if ( bAutoDetect == true )
			{
				bAutoDetect = false;
				bForceEnumOnly = true;
			} // Endif.

			if ( uiItemsCount > 0 )
			{
				oOutString.append ( szTemp );
			} // Endif.

			uiNameRealPos = GetSizeOfWhiteSpace ( szTokensString + uiCurPos, uiTknSize, uiNameRealSize );
			if ( uiNameRealPos != (unsigned int) -1 )
			{
				// Add this value to the output string:
				oOutString.append ( szTokensString + uiCurPos + uiNameRealPos, uiNameRealSize );
				uiItemsCount++;
			} // Endif.
		} // Endif.

		// Move to the next validation rule:
		if ( uiDtPos != (unsigned int) -1 )
		{
			uiCurPos += (uiDtPos + uiDtSize);

		} else
		{
			uiCurPos += uiTknSize;
		} // Endif.
		if ( ((uiRealSize - uiCurPos) > 0) && (szTokensString[uiCurPos] == cSeparatorChar) )
		{
			uiCurPos++;
		} // Endif.

		iLoopCount++;
	} // End of while loop.
}

bool GetValueFromList (
	const char *szList,
	std::string& oTypeOut,
	std::string& oNameOut,
	std::string& oValueOut,
	const char **ppNextValue
	)
{
	const char *pCur;    // Current position.
	const char *pStart;  // Start position of the current parsed string.
	int iState;          // Current state.
	int iDataType;       // Type data string to fill.
	unsigned int uiSize; // Size of the current parsed string.
	bool bBreakOut;      // Will be true to break out of the loop.

	// Initialize the local variables:
	iState = 0;
	iDataType = 0;
	oTypeOut = "";
	oNameOut = "";
	oValueOut = "";
	pStart = NULL;
	uiSize = 0;
	bBreakOut = false;
	if ( ppNextValue != NULL )
	{
		(*ppNextValue) = NULL;
	} // Endif.

	// Check for errors:
	if ( szList == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Loop on all the characters:
	pCur = szList;
	while ( (*pCur) != 0 )
	{
		// Check the state:
		switch ( iState )
		{
			// Find the type's start:
			case 0:
			case 4:
				if ( ((*pCur) != ' ') && ((*pCur) != '\t') && ((*pCur) != '\n') && ((*pCur) != '\r') )
				{
					if ( (*pCur) == ',' )
					{
						// Error:
						return false;
					} // Endif.

					if ( (*pCur) == '+' )
					{
						// Error:
						return false;
					} // Endif.

					if ( (*pCur) == '=' )
					{
						// Error:
						return false;
					} // Endif.

					if ( (*pCur) == '\"' )
					{
						pCur++;
						iState++;
						pStart = pCur;
						uiSize = 0;
						break;
					} // Endif.

					iState += 2;
					pStart = pCur;
					uiSize = 0;
					pCur++;

				} else
				{
					pCur++;
				} // Endif.
				break;

			// Find the end of a string - version 1:
			case 1:
			case 5:
				if ( (*pCur) == '\"' )
				{
					pCur++;
					iState += 2;

				} else
				{
					pCur++;
					uiSize++;
				} // Endif.
				break;

			// Find the end of a string - version 2:
			case 2:
			case 6:
				if ( ((*pCur) == ' ') || ((*pCur) == '\t') || ((*pCur) == '\n') || ((*pCur) == '\r') )
				{
					pCur++;
					iState++;

				} else
				{
					pCur++;
					uiSize++;
				} // Endif.
				break;

			// Locate '=':
			case 3:
				if ( ((*pCur) != ' ') && ((*pCur) != '\t') && ((*pCur) != '\n') && ((*pCur) != '\r') )
				{
					if ( (iDataType = ExtendedCompare ( (char *) pStart, (char *) "type;name;value", (int) uiSize, -1, false, true, true, true )) < 0 )
					{
						// Error:
						return false;

					} else
					{
						iDataType++;
					} // Endif.

					if ( (*pCur) != '=' )
					{
						// Error:
						return false;
					} // Endif.

					pCur++;
					iState++;

				} else
				{
					pCur++;
				} // Endif.
				break;

			// Locate either '+' or ',':
			case 7:
				if ( ((*pCur) != ' ') && ((*pCur) != '\t') && ((*pCur) != '\n') && ((*pCur) != '\r') )
				{
					switch ( iDataType )
					{
						// Type:
						case 1:
							oTypeOut = "";
							oTypeOut.append ( pStart, uiSize );
							break;

						// Name:
						case 2:
							oNameOut = "";
							oNameOut.append ( pStart, uiSize );
							break;

						// Value:
						case 3:
							oValueOut = "";
							oValueOut.append ( pStart, uiSize );
							break;

						// Unknown:
						default:
							// Error:
							return false;
					} // End of switch.

					if ( (*pCur) == ',' )
					{
						bBreakOut = true;
						pCur++;
						break;
					} // Endif.

					if ( (*pCur) != '+' )
					{
						// Error:
						return false;
					} // Endif.

					pCur++;
					iState = 0;

				} else
				{
					pCur++;
				} // Endif.
				break;

			// Unknown:
			default:
				// Error:
				return false;
		} // End of switch.

		if ( bBreakOut == true )
		{
			break;
		} // Endif.
	} // End of while loop.

	// We must be on state 7:
	if ( iState != 7 )
	{
		// Error:
		return false;
	} // Endif.

	if ( ppNextValue != NULL )
	{
		(*ppNextValue) = pCur;
	} // Endif.

	// That's all:
	return true;
}

const char *LocateCmdOnList (
	const char *szTokensString,
	const char *szCommandName,
	unsigned int& uiSizeOfValue,
	const char **ppNamePos,
	unsigned int& uiNameSize,
	unsigned int uiSizeOfTokensString,
	char cSeparatorChar,
	char cTokenValueChar,
	bool bIgnoreCommands
	)
{
	int iLoopCount;              // Loop counter.
	unsigned int uiDtPos;        // Data position.
	unsigned int uiDtSize;       // Data size.
	unsigned int uiTknSize;      // The size of the enum item name.
	unsigned int uiCurPos;       // Current token.
	unsigned int uiRealSize;     // The real size of the tokens string.
	unsigned int uiNameRealPos;  // Name real position.
	unsigned int uiNameRealSize; // Name real size.
	unsigned int uiItemsCount;   // Count of items been found.
	bool bForceEnumOnly;         // Will be true if it's not allowed to enter values other then on the validation string.
	bool bAutoDetect;            // Auto-detect if normal values allowed.

	// Do some calculations:
	uiRealSize = uiSizeOfTokensString;
	if ( uiRealSize == (unsigned int) -1 )
	{
		uiRealSize = strlen ( szTokensString );
	} // Endif.

	// Initialize the local variables:
	bForceEnumOnly = false;
	bAutoDetect = true;
	uiCurPos = 0;
	uiItemsCount = 0;
	uiNameSize = 0;
	uiSizeOfValue = 0;
	if ( ppNamePos != NULL )
	{
		(*ppNamePos) = NULL;
	} // Endif.

	// Loop on all the validation rules:
	iLoopCount = 0;
	while ( iLoopCount >= 0 )
	{
		// Get information about the current validation instruction:
		uiTknSize = GetTokenInfo ( szTokensString + uiCurPos, uiRealSize - uiCurPos, &uiDtPos, &uiDtSize, cSeparatorChar, cTokenValueChar );
		if ( uiTknSize == (unsigned int) -1 )
		{
			// End of the tokens string:
			break;
		} // Endif.

		// Check if this is a command:
		if ( (bIgnoreCommands == false) && (ExtendedCompare ( (char *) (szTokensString + uiCurPos), (char *) "@*", uiTknSize, -1, false, false, true, false, true ) == 0) )
		{
			// Check if this is our label:
			if ( ExtendedCompare ( (char *) (szTokensString + uiCurPos + 1), (char *) szCommandName, (int) (uiTknSize - 1), -1, false, false, true, false, true ) == 0 )
			{
				uiNameRealPos = GetSizeOfWhiteSpace ( szTokensString + uiCurPos, uiTknSize, uiNameRealSize );
				if ( (uiNameRealPos != (unsigned int) -1) && (uiNameRealSize > 0) )
				{
					if ( ppNamePos != NULL )
					{
						(*ppNamePos) = szTokensString + uiCurPos + uiNameRealPos;
					} // Endif.
					uiNameSize = uiNameRealSize;
				} // Endif.

				if ( (uiDtPos == (unsigned int) -1) || (uiDtSize == 0) )
				{
					// No data value:
					return NULL;
				} // Endif.

				uiSizeOfValue = uiDtSize;
				return szTokensString + uiCurPos + uiDtPos;
			} // Endif.
		} // Endif.

		// Move to the next validation rule:
		if ( uiDtPos != (unsigned int) -1 )
		{
			uiCurPos += (uiDtPos + uiDtSize);

		} else
		{
			uiCurPos += uiTknSize;
		} // Endif.
		if ( ((uiRealSize - uiCurPos) > 0) && (szTokensString[uiCurPos] == cSeparatorChar) )
		{
			uiCurPos++;
		} // Endif.

		iLoopCount++;
	} // End of while loop.

	// Command not been found:
	return NULL;
}

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
	)
{
	const char *szCurPos;     // Current position.
	unsigned int uiLoopCount; // Loop counter.
	unsigned int uiStartPos;  // Position of the last element.
	unsigned int uiSize;      // Element's size.
	int iState;               // Current state.

	// Initialize everything:
	oOutValue = "";
	uiNextMacroNamePos = (unsigned int) -1;
	uiNextMacroNameSize = 0;
	uiNextMacroValAPos = (unsigned int) -1;
	uiNextMacroValASize = 0;
	uiNextMacroValBPos = (unsigned int) -1;
	uiNextMacroValBSize = 0;
	uiNewSizeOfInput = 0;
	bIsError = false;
	uiLoopCount = 0;
	uiStartPos = 0;
	uiSize = 0;
	iState = 0;
	if ( szInput == NULL )
	{
		// Error:
		bIsError = true;
		return NULL;
	} // Endif.

	// Calculate the string's size:
	szCurPos = szInput;
	uiNewSizeOfInput = uiSizeOfInput;
	if ( uiNewSizeOfInput == (unsigned int) -1 )
	{
		uiNewSizeOfInput = strlen ( szCurPos );
	} // Endif.

	// While there're more characters to parse:
	while ( uiNewSizeOfInput > 0 )
	{
		// Check the current state:
		switch ( iState )
		{
			// Find data which is not macro:
			case 0:
				if ( (*szCurPos) == '@' )
				{
					if ( uiSize > 0 )
					{
						oOutValue.append ( szInput + uiStartPos, uiSize );
					} // Endif.

					uiStartPos = uiLoopCount + 1;
					uiSize = 0;
					iState = 1;

				} else
				{
					uiSize++;
				} // Endif.
				break;

			// Find the name of the macro command:
			case 1:
				// Command without any data parameter:
				if ( (*szCurPos) == '@' )
				{
					uiNextMacroNamePos = uiStartPos;
					uiNextMacroNameSize = uiSize;

					uiStartPos = uiLoopCount + 1;
					uiSize = 0;
					iState = 0;

					if ( uiSize == 0 )
					{
						oOutValue.append ( "@" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 't') )
					{
						oOutValue.append ( "\t" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'n') )
					{
						oOutValue.append ( "\n" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'r') )
					{
						oOutValue.append ( "\r" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 's') )
					{
						oOutValue.append ( " " );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'S') )
					{
						oOutValue.append ( ";" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'q') )
					{
						oOutValue.append ( "\"" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'Q') )
					{
						oOutValue.append ( "\'" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'e') )
					{
						oOutValue.append ( "=" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'c') )
					{
						oOutValue.append ( "," );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'd') )
					{
						oOutValue.append ( "." );

					} else
					{
						return szCurPos;
					} // Endif.

				// Command with one or more parameters:
				} else if ( (*szCurPos) == '!' )
				{
					uiNextMacroNamePos = uiStartPos;
					uiNextMacroNameSize = uiSize;

					uiStartPos = uiLoopCount + 1;
					uiSize = 0;
					iState = 2;

				} else if ( ((*szCurPos) == ' ') || ((*szCurPos) == '\t') || ((*szCurPos) == '\n') || ((*szCurPos) == '\t') )
				{
					if ( uiSize == 0 )
					{
						uiStartPos = uiLoopCount + 1;
					} // Endif.

				} else
				{
					uiSize = ((uiLoopCount - uiStartPos) + 1);
				} // Endif.
				break;

			// Find the first parameter:
			case 2:
				// Command without any data parameter:
				if ( (*szCurPos) == '@' )
				{
					uiNextMacroValAPos = uiStartPos;
					uiNextMacroValASize = uiSize;

					uiStartPos = uiLoopCount + 1;
					uiSize = 0;
					iState = 0;

					if ( uiSize == 0 )
					{
						oOutValue.append ( "@" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 't') )
					{
						oOutValue.append ( "\t" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'n') )
					{
						oOutValue.append ( "\n" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'r') )
					{
						oOutValue.append ( "\r" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 's') )
					{
						oOutValue.append ( " " );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'S') )
					{
						oOutValue.append ( ";" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'q') )
					{
						oOutValue.append ( "\"" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'Q') )
					{
						oOutValue.append ( "\'" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'e') )
					{
						oOutValue.append ( "=" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'c') )
					{
						oOutValue.append ( "," );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'd') )
					{
						oOutValue.append ( "." );

					} else
					{
						return szCurPos;
					} // Endif.

				// Command with one or more parameters:
				} else if ( (*szCurPos) == '!' )
				{
					uiNextMacroValAPos = uiStartPos;
					uiNextMacroValASize = uiSize;

					uiStartPos = uiLoopCount + 1;
					uiSize = 0;
					iState = 3;

				} else if ( ((*szCurPos) == ' ') || ((*szCurPos) == '\t') || ((*szCurPos) == '\n') || ((*szCurPos) == '\t') )
				{
					if ( uiSize == 0 )
					{
						uiStartPos = uiLoopCount + 1;
					} // Endif.

				} else
				{
					uiSize = ((uiLoopCount - uiStartPos) + 1);
				} // Endif.
				break;

			// Find the second parameter:
			case 3:
				// Command without any data parameter:
				if ( (*szCurPos) == '@' )
				{
					uiNextMacroValBPos = uiStartPos;
					uiNextMacroValBSize = uiSize;

					uiStartPos = uiLoopCount + 1;
					uiSize = 0;
					iState = 0;

					if ( uiSize == 0 )
					{
						oOutValue.append ( "@" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 't') )
					{
						oOutValue.append ( "\t" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'n') )
					{
						oOutValue.append ( "\n" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'r') )
					{
						oOutValue.append ( "\r" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 's') )
					{
						oOutValue.append ( " " );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'S') )
					{
						oOutValue.append ( ";" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'q') )
					{
						oOutValue.append ( "\"" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'Q') )
					{
						oOutValue.append ( "\'" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'e') )
					{
						oOutValue.append ( "=" );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'c') )
					{
						oOutValue.append ( "," );

					} else if ( (uiSize == 1) && (szInput[uiStartPos] == 'd') )
					{
						oOutValue.append ( "." );

					} else
					{
						return szCurPos;
					} // Endif.

				} else if ( ((*szCurPos) == ' ') || ((*szCurPos) == '\t') || ((*szCurPos) == '\n') || ((*szCurPos) == '\t') )
				{
					if ( uiSize == 0 )
					{
						uiStartPos = uiLoopCount + 1;
					} // Endif.

				} else
				{
					uiSize = ((uiLoopCount - uiStartPos) + 1);
				} // Endif.
				break;

			// Unknown state:
			default:
				// Error:
				bIsError = true;
				return NULL;
		} // End of switch.

		// Move to check the next character:
		szCurPos++;
		uiLoopCount++;
		uiNewSizeOfInput--;
	} // End of while loop.

	// Check for errors:
	if ( (uiSize > 0) || (iState > 0) )
	{
		// Error:
		bIsError = true;
		return NULL;
	} // Endif.

	// Return pointer other then NULL only if there're more characters to work on them:
	return (uiNewSizeOfInput > 0) ? NULL : szCurPos;
}

unsigned long TranslateToIp (
	const char *szInput,
	unsigned int uiSizeOfInput,
	bool *pbIsError
	)
{
	const char *pCur;        // Current positon.
	const char *pNext;       // Next positon.
	unsigned int uiSizeLeft; // Number of bytes left to parse.
	unsigned long uiOutVal;  // Output IP address.
	unsigned long uiDigit;   // Found IP segment.

	// Initialize the local variables:
	pCur = szInput;
	uiOutVal = 0;
	uiSizeLeft = uiSizeOfInput;
	if ( uiSizeLeft == (unsigned int) -1 )
	{
		uiSizeLeft = strlen ( szInput );
	} // Endif.

	// The string can't end here:
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// Get the next digit:
	uiDigit = (unsigned long) DecodeNumber ( pCur, 10, (int) uiSizeLeft, &pNext );
	if ( pCur == pNext )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string can't end here:
	uiSizeLeft -= (pNext - pCur);
	pCur = pNext;
	uiOutVal |= (uiDigit << 24);
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	if ( (*pCur) != '.' )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string can't end here:
	pCur++;
	uiSizeLeft--;
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// Get the next digit:
	uiDigit = (unsigned long) DecodeNumber ( pCur, 10, (int) uiSizeLeft, &pNext );
	if ( pCur == pNext )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string can't end here:
	uiSizeLeft -= (pNext - pCur);
	pCur = pNext;
	uiOutVal |= (uiDigit << 16);
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	if ( (*pCur) != '.' )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string can't end here:
	pCur++;
	uiSizeLeft--;
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// Get the next digit:
	uiDigit = (unsigned long) DecodeNumber ( pCur, 10, (int) uiSizeLeft, &pNext );
	if ( pCur == pNext )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string can't end here:
	uiSizeLeft -= (pNext - pCur);
	pCur = pNext;
	uiOutVal |= (uiDigit << 8);
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	if ( (*pCur) != '.' )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string can't end here:
	pCur++;
	uiSizeLeft--;
	if ( uiSizeLeft == 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// Get the next digit:
	uiDigit = (unsigned long) DecodeNumber ( pCur, 10, (int) uiSizeLeft, &pNext );
	if ( pCur == pNext )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	// The string must end here:
	uiSizeLeft -= (pNext - pCur);
	pCur = pNext;
	uiOutVal |= uiDigit;
	if ( uiSizeLeft != 0 )
	{
		if ( pbIsError != NULL )
		{
			(*pbIsError) = true;
		} // Endif.

		// Error:
		return 0;
	} // Endif.

	if ( pbIsError != NULL )
	{
		(*pbIsError) = false;
	} // Endif.

	// That's all:
	return uiOutVal;
}

bool CreateIpString (
	unsigned long dwIpAddress,
	std::string& oIpString
	)
{
	char szTemp[128]; // Temporary string.

	// Create the IP address string:
	sprintf_s ( szTemp, 127, "%u.%u.%u.%u", (unsigned int) (unsigned long) (dwIpAddress >> 24), (unsigned int) (unsigned long) ((dwIpAddress >> 16) & 255), (unsigned int) (unsigned long) ((dwIpAddress >> 8) & 255), (unsigned int) (unsigned long) (dwIpAddress & 255) );
	oIpString = szTemp;
	return true;
}

void BinToHexLine(
	const unsigned char *pData,
	char *szHexLine,
	unsigned int uiDataSize
	)
{
	unsigned int uiLoopCount; // Loop counter.
	unsigned int uiMaxBytes;  // Maximum number of bytes to convert.

	// Prepare the buffer:
	memset(szHexLine, ' ', 65);
	szHexLine[65] = 0;
	uiMaxBytes = uiDataSize > 16 ? 16 : uiDataSize;

	// Convert all the bytes:
	for (uiLoopCount = 0; uiLoopCount < uiMaxBytes; uiLoopCount++)
	{
		szHexLine[uiLoopCount + 49] = pData[uiLoopCount];
		if ((szHexLine[uiLoopCount + 49] < 32) || (szHexLine[uiLoopCount + 49] > 126))
		{
			szHexLine[uiLoopCount + 49] = '.';
		} // Endif.

		szHexLine[uiLoopCount * 3] = ((pData[uiLoopCount] >> 4) & 15);
		szHexLine[uiLoopCount * 3] += 0x30;
		if (szHexLine[uiLoopCount * 3] > 0x39)
		{
			szHexLine[uiLoopCount * 3] += 7;
		} // Endif.

		szHexLine[(uiLoopCount * 3) + 1] = (pData[uiLoopCount] & 15);
		szHexLine[(uiLoopCount * 3) + 1] += 0x30;
		if (szHexLine[(uiLoopCount * 3) + 1] > 0x39)
		{
			szHexLine[(uiLoopCount * 3) + 1] += 7;
		} // Endif.

		if (uiLoopCount == 8)
		{
			szHexLine[23] = '-';
		} // Endif.
	} // End of for loop.
}

//
// Private code:
//

//
// End of the source file string_parser.cpp
//

