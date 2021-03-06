/* Copyright (C) 2010, 2011  Olga Yakovleva <yakovleva.o.v@gmail.com> */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <windows.h>
#include <stdexcept>
#include "util.h"

using std::string;
using std::wstring;
using std::runtime_error;

string wstring_to_string(const wstring& src,bool utf8)
{
  if(src.empty())
    return string();
  UINT cp=utf8?CP_UTF8:CP_ACP;
  DWORD flags=utf8?0:WC_NO_BEST_FIT_CHARS;
  int size=WideCharToMultiByte(cp,flags,src.c_str(),-1,NULL,0,NULL,NULL);
  if(size==0)
    throw runtime_error("Unable to convert a string");
  string s(size,'\0');
  char *buff=new char[size];
  WideCharToMultiByte(cp,flags,src.c_str(),-1,buff,size,NULL,NULL);
  s.assign(buff);
  delete[] buff;
  return s;
}

wstring string_to_wstring(const string& src,bool utf8)
{
  if(src.empty())
    return wstring();
  UINT cp=utf8?CP_UTF8:CP_ACP;
  int size=MultiByteToWideChar(cp,0,src.c_str(),-1,NULL,0);
  if(size==0)
    throw runtime_error("Unable to convert a string");
  wstring s(size,'\0');
  wchar_t *buff=new wchar_t[size];
  MultiByteToWideChar(cp,0,src.c_str(),-1,buff,size);
  s.assign(buff);
  delete[] buff;
  return s;
}
