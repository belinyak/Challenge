@echo off
cls
set wildcard=*.hpp *.cpp *.h

echo -------------------------------
echo           TODOS
echo -------------------------------
FINDSTR /S /N /I /L "TODO" %wildcard%
:: /S	Searches for matching files in the current directory and all subdirectories.
:: /N	Prints the line number before each line that matches.
:: /I	Specifies that the search is not to be case-sensitive.
:: /L	Uses search strings literally.
echo -------------------------------

