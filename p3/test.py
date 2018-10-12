#!/usr/bin/python2

import os, sys
import fnmatch
import subprocess
from subprocess import PIPE
import filecmp
import locale
import shlex
__encoding = locale.getdefaultlocale()[1]


def testCode( retcode, msg ):
    if retcode > 0:
        print msg
        sys.exit( 1 )

testDir = os.path.join( os.getcwd(), 'cases/')
if not os.path.isdir( testDir ):
    print testDir, "isn't a directory"
    sys.exit( 1 )

executable = os.path.join(os.getcwd(), "prog")
if not os.path.isfile( executable ):
    retcode = subprocess.call("make",shell=True)
    testCode( retcode, "\tFAILED to make the scanner" )
with open("errors.dat", "w") as f:
    f.write("Error Log:\n")
f = open("errors.dat", "a")

files = os.listdir( testDir )
passed = 0
failed = 0
for x in files:
    if fnmatch.fnmatch(x, "*.py"):
        python_file_to_parse = os.path.join(testDir, x)

        our_process = subprocess.Popen( ["./prog", python_file_to_parse] , stdout=PIPE, stderr=PIPE, stdin=PIPE)
        our_output = our_process.communicate()
        our_output = sorted(our_output[0].split("\n"))

        mccabe_process = subprocess.Popen( ["radon", "cc", "-s", python_file_to_parse], stdout=PIPE, stderr=PIPE, stdin=PIPE)
        mccabe_output = mccabe_process.communicate()
        mccabe_output = sorted(mccabe_output[0].split("\n"))

        if our_output != mccabe_output:
            print "\ttestcase:", x, "FAILED"
            f.write("errors for {}\n----".format(python_file_to_parse))
            f.write(subprocess.Popen(["./script.sh", python_file_to_parse], stdout=PIPE, stderr=PIPE).communicate()[0])
            f.write("\n---END-----\n\n")
            failed += 1
        else:
            print "testcase:", x, "passed"
            passed += 1
print passed, "test cases passed"
print failed, "test cases failed"
f.close()
