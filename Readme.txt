----CPU schedulers----

I made these with a partner at my first university, Florida Atlantic University. It's been more than 5 years and I have since forgotten the finer details of how the schedulers work, but I do remember being quite proud of them.

Retested in Feb 2022 and they compiled as-is on Visual Studio Code with the appropriate 1st party C++ extension and Mingw-w64. If needed, follow the instructions in the 'Prerequisites' section on this link https://code.visualstudio.com/docs/cpp/config-mingw


----Oracle SQL----

IMPORTANT: This was written for Oracle's SQL syntax.

This demonstrates that I have basic working knowledge of SQL. It was written using Oracle's SQL*PLUS, to which access was provided to me by East Carolina University.

Context for the schema: Members can borrow books from the library. The number of books they can borrow is limited by the “limit” field of the Member relation (it may differ for different members). The category of a book includes fiction, non-fiction, children’s and reference. The CurrentLoan table represents the information about books that are currently checked out. When the book is returned to the library, the record will be removed from CurrentLoad relation, and will be inserted into History relation with the return-date. A library may have more than one copy of the same book, in which case each copy has its own bookID, but all copies share the same ISBN.

Retested in Feb 2022 using SQL Fiddle (sqlfiddle.com) and it works as expected. Table creation and insertion commands were copypasted into Fiddle's Schema panel. The queries are copypasted into the Query panel.

NOTE: The 'drop table' commands exist to prevent conflicts while using SQL*PLUS, especially when being run multiple times for testing. SQL Fiddle will complain about them and prevent the schema from being built, so those lines should be removed if testing on SQL Fiddle.


----HTML & CSS----

In the Using Templates folder is a few websites I made while I was learning how to work with HTML and CSS. For these I used a Bootstrap template, so I was also learning how to work with the Bootstrap library as well. I experimented with making tools, like a converter and a to-do list.

The From Scratch folder contains a site that I made with no template, to better learn how to use Bootstrap.

----Chat Program (C++)----

I worked with a partner to create a very simple network chat application. There are two chat applications, a server and a client. The server needs to be launched first.

These were originally created with Visual Studio 2019. When trying to compile with Visual Studio 2022, it may complain about outdated build tools. If this happens, the Visual Studio solution (.sln) files for both the client and server projects will need to be retargeted for the updated build tools.

----DVD Collection App (Java)----

I created a rudimentary DVD collection application with a text-based UI to be used through a terminal. It supports 6 functions: adding new entry, changing existing entry, searching for entry, display by category, remove entry, and saving data.

