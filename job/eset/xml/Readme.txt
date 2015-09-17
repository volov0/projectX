Programming Task Objective
--------------------------

Create a multi-threaded program in C++ that processes a simple XML file (see
"index.xml").  The program shall remove non-text elements, specifically the
<img>, <script>, <object> tags, and their enclosed content from the input
file.  All other tags and the text content should be kept in the output.
Program should write the output to a new file.

You are not allowed use a XML parser library, you must implement your own
simplified XML parsing.  It is enough to recognize "<", ">" and "/" when
parsing the XML elements, i.e.  "<tag id='1'>", "</tag>" and "<tag/>".  Input
text may only contain 7 bit ASCII and no escape characters or entity
references. (E.g. "&quot;" or "&#34;" cannot appear in the input document.)

Program should use two threads.

 - One for reading and parsing the XML, getting the output from a second
   thread and writing it to the output file.
 - The second thread should implement a "tag-filter" by filtering the non-text
   elements, <img>, <script> and <object>.

The first "XML-parsing" thread should pass data to the second thread as soon as
possible.  Similarly, the second "tag-filter" thread should output filtered
data as soon as possible and therefore not to cache them unnecessarily.  Your
algorithm should allow these two threads to run simultaneously with minimal
locking.

Using libraries like Boost is possible, but not necessary.  As a hint, you can
use a built-in support for multi-threaded programming introduced in C++11:
<http://en.cppreference.com/w/cpp/thread>.

Your solution could be completely cross-platform.  However, we will appreciate
if we can easily compile and evaluate it using "Visual Studio Express 2013 for
Windows Desktop" or "Visual Studio 2015".

We expect you to use modern C++ programing techniques when solving this
task.  Don't over-design or under-design and make sure you manage your memory
correctly.

A sample XML file is attached.


Programming Task Evaluation
---------------------------

When evaluating your solution we will consider:

 1. Correctness.
 2. Code clarity.
 3. Efficiency.
 4. Documentation.
 5. Robustness.


Good luck.  
ESET Engineering Team



