import os

#lsb_release = os.popen('lsb_release --short --release').read().strip()
#print("LSB RELEASE is %s" % lsb_release)
#COMPILER_PATH = '/opt/praxis/local/el-%s/gcc-4.8.2/bin' % lsb_release

envPath = [ #COMPILER_PATH,
            '/bin',
            '/usr/bin' ]
#print("Path is %s" % str(envPath))

vanillaLibs = ['pthread', 'boost_filesystem','boost_system', 'jsoncpp']

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
    return vanillaEnv.Object('%s.cpp' % x )

mmapper, pingPong, mpmc, rateTimer, trade, tradeServer, vwap  = [ makeObject(x) for x in 'mmapper,pingPong,mpmc,rateTimer,trade,tradeServer,vwap'.split(',') ]

testRateTimer = vanillaEnv.Program('testRateTimer',['testRateTimer.cpp'  , rateTimer] )
ping          = vanillaEnv.Program('ping', ['ping.cpp', pingPong, mmapper, rateTimer] )
pong          = vanillaEnv.Program('pong', ['pong.cpp', pingPong, mmapper, rateTimer] )
jsonexample = vanillaEnv.Program('jsonExample', ['jsonExample.cpp'], LIBS= vanillaLibs + ['docopt'] )

progs = [ 'move',
          'relations',
          'moveTest2',
          'traits',
          'forwarding',
          'forwarding2',
          'twonk',
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
          'packFun', #Wait for 17 :-) for the commented one
          'moveCapture',
          'initList',
          'chatServer',
          'bindFun',
          #'chain'
          'stringReverse',
          'arrayDecay',
          'scopeExperiment',
          'lineReader',
          'boostRefCountExample',
          'filesystemExperiment',
          'destructor',
          'printTest',
          #'virtualExperiment',
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
          #'thread_fun',
          'foo',
          'moveTest3',
          'bindExample',
          #'ctad',
          'overloaded',
          'fileSystem',
          #'tradeSourceImpl'
          'sink',
          'boost_shared_memory',
          #'crtp3'
          'optimizer',
          'foldExpression',
          #'crtp4'
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
          'exprtk_sqrt_newton_raphson'
          ]

#progs = [ 'exprtk_sqrt_newton_raphson' ]


[ vanillaEnv.Program( '%s.cpp' % x ) for x in progs ]

vanillaEnv.Program('epoll_example.c')

box2dEnv = vanillaEnv.Clone()

tbbEnv = vanillaEnv.Clone()
tbbEnv.Program('active_object.cpp', CPPFLAGS=['-DTBB_USE_DEBUG=1'], LIBS = ['tbb', 'pthread'])
tbbEnv.Program('queue_test.cpp', CPPFLAGS=['-DTBB_USE_DEBUG=1'], LIBS = ['tbb', 'pthread'])

#helloWorld = box2dEnv.Program('box2d_helloworld.cpp', LIBS=['Box2D'])

mpmcTest   = vanillaEnv.Program('testMpmc'  , source = [ 'testMpmc.cpp'  ,mpmc] )
mpmcSanity = vanillaEnv.Program('mpmcSanity', source = [ 'mpmcSanity.cpp',mpmc] )

sharedFromThisTest = vanillaEnv.Program('sharedFromThisTest.cpp')

xcbExample = vanillaEnv.Program('xcbexample.cpp', LIBS = ['xcb'])

tradeReader          = vanillaEnv.Program('tradeReader', ['tradeReader.cpp', mmapper, trade] )
tradeServerMain = vanillaEnv.Program('tradeServerMain', ['tradeServerMain.cpp', tradeServer, mmapper, trade] )
tradeClientMain = vanillaEnv.Program('tradeClientMain', ['tradeClientMain.cpp', mmapper, trade] )
tradeSourceImpl = vanillaEnv.Program('tradeSourceImpl', ['tradeSourceImpl.cpp', mmapper, trade] )

vwapNetworkClient = vanillaEnv.Program('vwapNetworkClient', ['vwapNetworkClient.cpp', mmapper, trade] )


