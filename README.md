libdelimText
============
The goal of this library is to simply and consistently read/process delimited text data for use in other applications such as [datatime](https://github.com/mkucenski/datatime) or [fw2mactime](https://github.com/mkucenski/fw2mactime).

License
-------
Copyright &copy; 2007 Matthew A. Kucenski

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at: http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Detailed Description
--------------------

### Classes
* textFile - basic class to abstract any text file
* delimTextFile - derives from 'textFile' and provides access to the delimited text such as a 'CSV' file.
* delimTextRow - class to abstract individual delimited text file rows.

Dependencies
------------
* [Boost](http://www.boost.org)

Notes
-----
