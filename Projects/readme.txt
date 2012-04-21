Test your code with these test cases before submitting, to ensure there are no formatting errors in your code.
Use p3test1.sh script to test your code, you need to have test cases in a folder named Tests and have an empty
folder named Output (your program output and diff files will be generated there) and then your compiled program
should be a file named a.out, Here is the required directory structure:
-- 
  |-- p3test1.sh
  |-- a.out
  |-- Tests/
       |-- test01.txt
       |-- test01.txt.expected
       |-- test02.txt
       |-- ...
  |-- Output/

You should also have execute permission on p3test1.sh, you can give execution permission to a file using chmod command (chmod 770 <filename>)
When you run the script (by ./p3test1.sh) it deletes all files in Output folder then for each test in Tests folder, runs your program (a.out)
by redirecting standard input to test file and standard output to a file with .output extension in Output folder. Then it uses diff -ibadBw 
to compare your program's output with .expected file and saves the result of diff in a file with .diff extension in Output folder. 
If the .diff file has 0 bytes it is considered passed, but if there is something in the file the contents will be shown to you. At the end 
script reports number of errors encountered.

