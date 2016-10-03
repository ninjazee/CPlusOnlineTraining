import os, sys, getopt, zipfile, operator

help_string = 'ValidateSolutions.py --continue --help --name <name> --prog <inputfile> --data <outputfile>'

def main( argv):
    prog = ''
    problem = ''
    zipdata = ''
    nonstop = False
    try:
        opts, args = getopt.getopt(argv, "chp:d:n:",["help","prog=","data=","name=", "continue"])
    except getopt.GetoptError:
        print( 'GetOptionError')
        print ( help_string )
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print ('Help')
            print (help_string ) 
            sys.exit()
        elif opt in ("-p", "--prog"):
            prog = arg
        elif opt in ("-d", "--data"):
            zipdata = arg; 
        elif opt in ("-n", "--name"):
            problem = arg; 
        elif opt in ("-c","--continue"):
            nonstop = True;
        else:
            print( 'Opt:', opt, ' Argument:', arg ); 
    if ( prog == '' or zipdata =='' ):
        print (help_string ) 
        sys.exit()
    path, exe = os.path.split( prog );
    if ( problem=='' ):
        problem, _ = os.path.splitext(exe)
    print 'Execution Path:', path, ' Name:', problem

    if os.path.exists(problem + '.in' ):
        os.remove( problem + '.in' )
    if os.path.exists(problem + '.out' ):
        os.remove( problem + '.out' )
    zfile = zipfile.ZipFile(zipdata)
    dicIn = {};
    dicOut = {};
    dicAll = {};
    for name in zfile.namelist():
        (dirname,filename) = os.path.split(name)
        inPos = filename.find(".in");
        if ( inPos >=0 ):
            dicIn[ filename[0:inPos ]] = filename; 
            dicAll[ filename[0:inPos ]] = int(filename[0:inPos ]); 
        outPos = filename.find(".out");
        if ( outPos >=0 ):
            dicOut[ filename[0:outPos ]] = filename; 
            dicAll[ filename[0:outPos ]] = int(filename[0:outPos ]); 
    # print(dicAll);
    sortedList =sorted(dicAll, key = dicAll.get ); 
    # print(sortedList);
    # os.chdir( path ) 
    error = False
    for name in sortedList:
        if name not in dicIn.keys():
            print 'Output data ', dicOut[name], ' has no associated input data'
        elif name not in dicOut.keys():
            print 'Input data ', dicIn[name], ' has no associated output data' 
        else:
            print '==== Evaluate ',dicIn[name], ':',dicOut[name],'================='
        zfile.extract( dicIn[name], path )
        zfile.extract( dicOut[name], path )
        # Execute the code
        # print 'Rename', dicIn[name], ' to ', problem+'.in'
        os.rename( dicIn[name], problem+'.in')
        os.system( prog )
        # Compare two text file. 
        output1 = open( problem+'.out', 'r' )
        output2 = open( dicOut[name], 'r' )
        lines1 = output1.readlines()
        lines2 = output2.readlines()
        output1.close()
        output2.close()
        nlines1 = len(lines1)
        nlines2 = len(lines2)
        if nlines1 != nlines2:
            print 'Different output file length', nlines1, ' vs ', nlines2
            error = True
        for i in range(nlines1):
            if lines1[i]!=lines2[i]:
                print 'Mismatch on line: ', i
                error = True
        if error:
            print '============= Input file', problem+'.in', ' ==================='
            #infile = open( problem +'.in' )
            #inlines = infile.readlines()
            #for line in inlines:
            #    print line
            #infile.close();
            print '============= Output file', problem+'.out', ' ==================='
            for line in lines1:
                print line
            print '============= Desired Output file', dicOut[name] , ' ==================='
            for line in lines2:
                print line
            if not nonstop:
                sys.exit(2)
        os.remove( problem+'.in' )
        os.remove( problem+'.out' )
        os.remove( dicOut[name] )

if __name__ == "__main__":
    main(sys.argv[1:])

