--[[
	22. Operating System Facilities
]]

-- In any application, it is often required for to access Operating System level functions and it is made available with Operating System library. The list of functions available are listed in the following table.

S.N.	Library / Method & Purpose
1.	
os.clock ()

Returns an approximation of the amount in seconds of CPU time used by the program.

2.	
os.date ([format [, time]])

Returns a string or a table containing date and time, formatted according to the given string format.

3.	
os.difftime (t2, t1)

Returns the number of seconds from time t1 to time t2. In POSIX, Windows, and some other systems, this value is exactly t2-t1.

4.	
os.execute ([command])

This function is equivalent to the ANSI C function system. It passes command to be executed by an operating system shell. Its first result is true if the command terminated successfully, or nil otherwise.

5.	
os.exit ([code [, close])

Calls the ANSI C function exit to terminate the host program. If code is true, the returned status is EXIT_SUCCESS; if code is false, the returned status is EXIT_FAILURE; if code is a number, the returned status is this number.

6.	
os.getenv (varname)

Returns the value of the process environment variable varname, or nil if the variable is not defined.

7.	
os.remove (filename)

Deletes the file (or empty directory, on POSIX systems) with the given name. If this function fails, it returns nil, plus a string describing the error and the error code.

8.	
os.rename (oldname, newname)

Renames file or directory named oldname to newname. If this function fails, it returns nil, plus a string describing the error and the error code.

9.	
os.setlocale (locale [, category])

Sets the current locale of the program. locale is a system-dependent string specifying a locale; category is an optional string describing which category to change: "all", "collate", "ctype", "monetary", "numeric", or "time"; the default category is "all". The function returns the name of the new locale, or nil if the request cannot be honored.

10.	
os.time ([table])

Returns the current time when called without arguments, or a time representing the date and time specified by the given table. This table must have fields year, month, and day, and may have fields hour (default is 12), min (default is 0), sec (default is 0), and isdst (default is nil). For a description of these fields, see the os.date function.

11.	
os.tmpname ()

Returns a string with a file name that can be used for a temporary file. The file must be explicitly opened before its use and explicitly removed when no longer needed.

Common OS functions
A simple example using common math functions is shown below.

-- Date with format
io.write("The date is ", os.date("%m/%d/%Y"),"\n")

-- Date and time
io.write("The date and time is ", os.date(),"\n")

-- Time
io.write("The OS time is ", os.time(),"\n")

-- Wait for some time
for i=1,1000000 do
end

-- Time since Lua started
io.write("Lua started before ", os.clock(),"\n")
When we run the above program, we will get similar output to the following.

The date is 01/25/2014
The date and time is 01/25/14 07:38:40
The OS time is 1390615720
Lua started before 0.013
The above examples are just a few of the common examples, we can use OS library based on our need, so try using all the functions to be more familiar. There are functions like remove which helps in removing file, execute that helps us executing OS commands as explained above.
