import os

#lsb_release = os.popen('lsb_release --short --release').read().strip()
#print("LSB RELEASE is %s" % lsb_release)
#COMPILER_PATH = '/opt/praxis/local/el-%s/gcc-4.8.2/bin' % lsb_release

envPath = [ #COMPILER_PATH,
            '/bin',
            '/usr/bin' ]
#print("Path is %s" % str(envPath))

#vanillaLibs = ['pthread', 'boost_filesystem','boost_system', 'jsoncpp']

vanillaLibs = []

vanillaEnv = Environment(
    #CPPPATH   = ['/home/andy/include'],
    #CPPFLAGS  = ['-std=c++14', '-O3', '-Wall'], 
    CPPFLAGS  = ['-std=c++23', '-g'],
    CXXFLAGS  = ['-std=c++23', '-g'],
    LIBS = vanillaLibs
    #LIBS      = ['stdc++'],'boosat_filesystem_', 'boost_system'],
    #LINKFLAGS = ['-L/usr/lib64'],
    #ENV       = {
    #'PATH' : ":".join(envPath)
    #}
)

vanillaEnv.Tool('compilation_db')
vanillaEnv.CompilationDatabase()

def makeObject(x):
    return vanillaEnv.Object(source = f'{x}.cpp', target = f'build/{x}.o')

mmapper, pingPong, mpmc, rateTimer, trade, tradeServer, vwap  = [ makeObject(x) for x in 'mmapper,pingPong,mpmc,rateTimer,trade,tradeServer,vwap'.split(',') ]

progs = [ 'move',
          'relations',
          'moveTest2',
          'traits',
          'forwarding',
          'forwarding2',
          'doit',
          'lockExperiment',
          'tmp',
          'lfq',
          'rdtsc',
          'intraProcessPingPong',
          'myers',
          'crtp',
          'crtp2',
          'tupple',
          'exper',
          'funcStuff',
          'async',
          'transform',
          'transform3',
          'condition',
          'tupleFun',
          'pointerFun',
          'socketServer',
          'pmf',
          'ecpp2',
          'ecpp4',
          'rose',
          'selectif',
          'abbrev',
          'constVec',
          'erasure',
          'logExperiment',
          'backInserterEquiv',
          'socketServer2',
          'transform2',
          'echoServer',
          'parameterPack',
          'threadTest',
          'myers2',
          'memfunStuff',
          'vectorCast',
          'property_tree',
          'lambdaTemplate',
          'tcpclient',
          'tupleInit',
          'knightTour',
          'knightTour2',
          'helloWorld',
          'stringTest',
          'testPrettyPrint',
          'myPromise',
          'cherryPick',
          'packFun',
          'moveCapture',
          'initList',
          'chatServer',
          'bindFun',
          'stringReverse',
          'arrayDecay',
          'scopeExperiment',
          'lineReader',
          'boostRefCountExample',
          'destructor',
          'printTest',
          'virtualExperiment2',
          'dynclass',
          'except',
          'stringReverse2',
          'synctimer',
          'timer',
          'periodic',
          'functors',
          'daytimeClient',
          'daytimeServer',
          'asyncDatetimeServer',
          'streambuf_example',
          'read_until_example',
          'baseTest',
          'read_a_file',
          'vector_test',
          'complex_test',
          'destructure',
          'copy_test',
          'vectorfun',
          'transform_test',
          'overload',
          'testb',
          'maptest',
          'mutabletest',
          'google',
          'jen',
          'foo',
          'moveTest3',
          'bindExample',
          'overloaded',
          'sink',
          'boost_shared_memory',
          'optimizer',
          'foldExpression',
          'owner',
          'variadic',
          'sfinae',
          'sfinae2',
          'stdalign',
          'noexcept',
          'nomove',
          'elision',
          'exceptions',
          'marketDataExample',
          'shared_lock',
          'finalizer',
          'hammer',
          'arrayTest',
          'polygon',
          'stairs',
          'helloWorld',
          'exprtk_sqrt_newton_raphson',
          'sharedFromThisTest'
          ]





def makeProgram(prog, **kwargs):
    o = vanillaEnv.Object( source = f'{prog}.cpp' ,target=f'build/{prog}')
    vanillaEnv.Program(source = o, target = f'bin/{prog}', **kwargs)


    
for prog in progs:
    makeProgram(prog)

makeProgram('twonk'     , LIBS = ['boost_system', 'boost_filesystem'])
makeProgram('fileSystem', LIBS = ['boost_system', 'boost_filesystem'])
makeProgram('filesystemExperiment',LIBS = ['boost_system', 'boost_filesystem'])
makeProgram('testRateTimer', LIBS = [rateTimer])
makeProgram('ping', LIBS = [pingPong, mmapper, rateTimer] )
makeProgram('pong', LIBS = [pingPong, mmapper, rateTimer] )
makeProgram('jsonExample', LIBS = ['jsoncpp', 'docopt'] )
makeProgram('active_object', CPPFLAGS=['-DTBB_USE_DEBUG=1'], LIBS = ['tbb', 'pthread'])
makeProgram('queue_test',    CPPFLAGS=['-DTBB_USE_DEBUG=1'], LIBS = ['tbb', 'pthread'])
makeProgram('testMpmc',    LIBS = [mpmc])
makeProgram('mpmcSanity',  LIBS = [mpmc] )
makeProgram('xcbexample',  LIBS = ['xcb'])
makeProgram('tradeReader', LIBS = [mmapper, trade])
makeProgram('tradeServerMain', LIBS = [tradeServer, mmapper, trade])
makeProgram('tradeClientMain', LIBS = [ mmapper, trade] )
makeProgram('tradeSourceImpl', LIBS = [mmapper, trade]) 
makeProgram('vwapNetworkClient', LIBS = [mmapper, trade] )


